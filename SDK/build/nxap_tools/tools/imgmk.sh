#!/bin/bash
source ./input/script.cfg

cleanup()
{
    if [ "$DEBUG" != "debug" ];then
        rm -f *.bin *.sig *.hash *.tmp  manifest*.cfg\
              image.key image.key.des3 *.o program.out image.ld *.prencrypt\
              *.prelz
    fi
}

EXIT()
{
    echo "Error: generation fail on line $1"
    echo "========================"
    echo "Image Generation Failed"
    echo "========================"
#    cleanup
    exit 1
}

image_process()
{
    eval TMP_IMGNUM="\$IMGNUM$1"
    sed -i "s/#define    IMAGE_NUM.*/#define    IMAGE_NUM       $TMP_IMGNUM/g" src/manifest.h
    gcc src/output_gen.c -o output_gen -g || EXIT  $LINENO
    ## prepare input for manifest generation ##
    echo VERSION=$VERSION >manifest$2.cfg
    echo DIGSCH=$DIGSCH >>manifest$2.cfg
    echo SIGSCH=$SIGSCH >>manifest$2.cfg
    echo IMGNUM=$IMGNUM >>manifest$2.cfg
    echo MANIFEST1_START=$(($MANIFEST1_START))>>manifest$2.cfg
    echo MANIFEST2_START=$(($MANIFEST2_START))>>manifest$2.cfg
    if [[ "$BOOT_IDX" < "1" ]] || [[  "$BOOT_IDX" > "$TMP_IMGNUM" ]];then
        echo "System image idx out of range!"
    fi
    echo BOOT_IDX=$BOOT_IDX >>manifest.cfg
    IMGSTART=0
    IMGEND=0
    for i in $(seq $(($TMP_IMGNUM))); do
        ## get image information from config ##
        eval TMP_PATH="\$IMAGE${i}$1"
        eval TMP_ENC="\$IMAGE${i}_ENC$1"
        eval TMP_COPY="\$IMAGE${i}_COPY$1"
        eval TMP_IDX="\$IMAGE${i}_IDX$1"
        eval TMP_FORMAT="\$IMAGE${i}_FORMAT$1"
        eval TMP_IDX="\$IMAGE${i}_IDX$1"
        ## check input ##
        if [ -z "$TMP_PATH" ] || [ -z "$TMP_ENC" ] || [ -z "$TMP_COPY" ] || [ -z "$TMP_IDX" ] ||\
           [ -z "$TMP_FORMAT" ] ;then
            echo "Please specify image information(PATH, ENC, COPY, LOADADDR, IDX, FORMAT)"\
                  "in script.cfg!"
            exit 1
        fi
        ## convert image to binary ##
        if [ "$TMP_FORMAT" = "bin_elf" ] ;then
            TMP_LOADADDR=`${CROSS_TOOL}readelf -l $TMP_PATH|grep LOAD|awk '{print $3}'|awk 'NR==1{print}'`
            ${CROSS_TOOL}objcopy -O binary $TMP_PATH image${i}$2.bin
        elif [ "$TMP_FORMAT" = "bin_raw" ];then
            cp $TMP_PATH image${i}$2.bin
        else
            echo "Unsupport file format!"
            EXIT  $LINENO
        fi
        ./alignment image${i}$2.bin
        IMGSIZE=`ls -l image${i}$2.bin|awk '{print $5}'`
        eval TMP_ADDR="\$IMAGE${i}_LOADADDR$1"
        if [ ! -z "$TMP_ADDR" ] ;then
            TMP_LOADADDR="$TMP_ADDR"
        fi
        ## encryption ##
        if [ "$TMP_ENC" = "1" ] ;then
            sha1sum image${i}$2.bin| awk '{print $1}' > image${i}$2.hash || EXIT  $LINENO
            ./hextobin  image${i}$2.hash image${i}$2.hash.bin || EXIT  $LINENO
            if [ "$SIG_FORMAT" = "DES" ] ;then
                openssl enc -des-ede -nosalt -K $TBKEY -iv 0 -in\
                        image${i}$2.hash.bin -out image${i}$2.sig || EXIT  $LINENO
            else
                openssl rsautl -encrypt -pkcs -in image${i}$2.hash.bin -inkey\
                        $RSAPRIV -out image${i}$2.sig -sign || EXIT  $LINENO
            fi
            mv image${i}$2.bin image${i}$2.bin.prencrypt
            openssl enc -aes-128-ecb -nosalt -K $IMGKEY -iv 0 -in image${i}$2.bin.prencrypt\
                    -out image${i}$2.bin || EXIT  $LINENO
        fi
        if [ "$TMP_ENC" = "3" ] ;then
            echo "Compressing image ${i}: ${TMP_PATH##*/}"
            mv image${i}$2.bin image${i}$2.bin.prelz
            ./input/lz77 -i image${i}$2.bin.prelz image${i}$2.bin
            IMGSIZE=`ls -l image${i}$2.bin|awk '{print $5}'`
        fi
        ## output config file ##
        echo IMG${i}NAME=${TMP_PATH##*/} >>manifest$2.cfg
        echo IMG${i}ENC=${TMP_ENC} >>manifest$2.cfg
        echo IMG${i}COPY=${TMP_COPY} >>manifest$2.cfg
        echo IMG${i}LOADADDR=$((${TMP_LOADADDR})) >>manifest$2.cfg
        echo IMG${i}IDX=${TMP_IDX} >>manifest$2.cfg
        echo IMG${i}SIZE=$IMGSIZE >>manifest$2.cfg
        IMGSTART=$IMGEND
        echo IMG${i}START=$IMGSTART>>manifest$2.cfg
        IMGEND=$(($IMGEND+(IMGSIZE/$ALIGNMENT)*$ALIGNMENT+$ALIGNMENT*2))
    done;
    echo IMGEND=$IMGEND>>manifest$2.cfg

    ## generate manifest, bootcfg, and pack images ##
    ./output_gen $2|| EXIT  $LINENO
    sha1sum manifest$2.out| awk '{print $1}'  > manifest$2.hash || EXIT  $LINENO
    ./hextobin  manifest$2.hash manifest$2.hash.bin || EXIT  $LINENO
    if [ "$SIG_FORMAT" = "DES" ] ;then
        openssl enc -des-ede -nosalt -K $TBKEY -iv 0 -in manifest$2.hash.bin\
                -out manifest$2.sig || EXIT  $LINENO
    else
        openssl rsautl -encrypt -pkcs -in manifest$2.hash.bin -inkey $RSAPRIV\
                -out manifest$2.sig -sign || EXIT  $LINENO
    fi
    cat manifest$2.sig>>manifest$2.out
}

run_build()
{
    gcc src/hextobin.c -o hextobin -g || EXIT  $LINENO
    gcc src/alignment.c -o alignment -g || EXIT  $LINENO
    ## get key from file ##
    IMGKEY=`grep key $AESKEY|sed 's/key=//g'`
    BOOTKEY=`grep key $DESKEY|sed 's/key=//g'`
    if [ "$SIG_FORMAT" = "DES" ] ;then
        TBKEY=`grep key $TRUSTBOOTKEY|sed 's/key=//g'`
    fi
    ## caculate image key address ##
    FILEADDR=`${CROSS_TOOL}readelf -l $BOOT|grep LOAD|head -1|awk '{print $2}'`
    LOADADDR=`${CROSS_TOOL}readelf -l $BOOT|grep LOAD|head -1|awk '{print $3}'`
    KEYADDR=$((16#`${CROSS_TOOL}readelf -s $BOOT|grep image_key|head -1|awk '{print $2}'`))
    OFFSET=$(($KEYADDR-$LOADADDR+$FILEADDR))

    ## generate utils ##
    ## insert key into bootload and generate binary output ##
    echo $IMGKEY >image.key
    ./hextobin image.key image.key.bin || EXIT  $LINENO
    openssl enc -des-ede -nosalt -K $BOOTKEY -iv 0 -in image.key.bin -out image.key.des3\
            || EXIT  $LINENO
#    ./key_insert $BOOT $OFFSET ./image.key.des3 || EXIT  $LINENO
#    ${CROSS_TOOL}objcopy -O binary bootload.tmp boot.out
    ${CROSS_TOOL}objcopy -O binary $BOOT boot.out

    ## process image for primary and update ##
    image_process
    if [ "$HAVE_UPDATE" = "1" ] ;then
        image_process _UPDATE .update
    fi

    ## link the output and generate bin and ihex output ##
    cp  input/image.ld.in   ./image.ld
    sed -i "s/SIZE_LIMIT/$SIZE_LIMIT/g" image.ld
    ${CROSS_TOOL}ld -r -EL  -o btupdate1.o -bbinary btupdate1.out
    ${CROSS_TOOL}ld -r -EL  -o btupdate2.o -bbinary btupdate2.out
    ${CROSS_TOOL}ld -r -EL  -o boot.o -bbinary boot.out
    ${CROSS_TOOL}ld -r -EL  -o image.o -bbinary image.out
    ${CROSS_TOOL}ld -r -EL  -o bootcfg.o -bbinary bootcfg.out
    ${CROSS_TOOL}ld -r -EL  -o manifest.o -bbinary manifest.out
    if [ "$HAVE_UPDATE" = "1" ] ;then
        ${CROSS_TOOL}ld -r -EL  -o image.update.o -bbinary image.update.out
        ${CROSS_TOOL}ld -r -EL  -o manifest.update.o -bbinary manifest.update.out
        UPDATEINPUT="image.update.o manifest.update.o"
    fi

    ${CROSS_TOOL}ld bootcfg.o btupdate1.o btupdate2.o boot.o  image.o  manifest.o $UPDATEINPUT -T image.ld -o program.out || EXIT  $LINENO
    ${CROSS_TOOL}objcopy -O binary program.out program.binary
    ${CROSS_TOOL}objcopy -O ihex program.out program.ihex
#    cleanup
    echo "========================"
    echo "Image Generation Succeed"
    echo "========================"
}

run_clean()
{
    echo "rm -f boot.out image.out manifest.out bootcfg.out program.ihex program.binary"
    rm -f boot.out image.out manifest.out bootcfg.out program.ihex program.binary image.update.out manifest.update.out
#    cleanup
}

if [ "$1" = "--help" ] || [ "$1" = "-h" ] || [ "$1" = "--h" ];then
    echo "$0        :To build file"
    echo "$0 clean  :To clean out file"
    exit 0
elif [ "$1" = "clean" ];then
    run_clean
elif [ "$1" = "debug" ];then
    DEBUG="debug"
    run_build
elif [ -z "$1" ];then
    run_build
else
    echo "Error options: $@"
    exit 1
fi

