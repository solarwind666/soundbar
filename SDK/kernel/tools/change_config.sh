#!/bin/bash

KEY="CONFIG_NGHTTP2 "
MATCH="CONFIG_MTD "
CUR_PATH=$(pwd)
CONFIG_FILE_OUT=${CUR_PATH}/include/nuttx/config.h
CONFIG_FILE_IN_S=${CUR_PATH}/tools/config_mem_small.cfg
CONFIG_FILE_IN_B=${CUR_PATH}/tools/config_mem_big.cfg
#SCPRIT_CFG=${CUR_PATH}/hardware/id.bsp/configs/${CONFIG_ARCH_CHIP}/${CONFIG_ARCH_BOARD}/DVT/script.cfg
grep -ir $KEY $CONFIG_FILE_OUT > /dev/null
if [ $? -eq 0 ]; then
    echo "found nghttp2"
    index=0
    while read LINE
    do
#        echo "$LINE"
        mtd[$index]=$LINE
#        echo "index:$index"
        echo "mtd[$index]:${mtd[$index]}"
        index=$[($index+1)]
    done < $CONFIG_FILE_IN_B
    while [[ $index -gt 0 ]];do
        index=$[($index-1)]
        val=${mtd[$index]};
#        echo "index:$index"
        echo "val:$val"
        sed -i "/$MATCH/a$val" $CONFIG_FILE_OUT
    done
#    sed -i "s/SIZE_LIMIT=0x[0-9]*/SIZE_LIMIT=0x500000/g" $SCPRIT_CFG
#    sed -i "/$MATCH/a\"" $CONFIG_FILE_OUT
else
    echo "not found nghttp2"
    index=0
    while read LINE
    do
#        echo "$LINE"
        mtd[$index]=$LINE
#        echo "index:$index"
        echo "mtd[$index]:${mtd[$index]}"
        index=$[($index+1)]
    done < $CONFIG_FILE_IN_S
    while [[ $index -gt 0 ]];do
        index=$[($index-1)]
        val=${mtd[$index]};
#        echo "index:$index"
        echo "val:$val"
        sed -i "/$MATCH/a$val" $CONFIG_FILE_OUT
    done
#    sed -i "s/SIZE_LIMIT=0x[0-9]*/SIZE_LIMIT=0x500000/g" $SCPRIT_CFG
#    sed -i "/$MATCH/a\"" $CONFIG_FILE_OUT
fi
