#!/bin/bash

BASE=`pwd`

#set -x

#function declaring
declare -a _inlist
function select_choice()
{
    _target_arg=$1
    _arg_list=(${_inlist[@]})
    _outc=""
    select _c in ${_arg_list[@]}
    do
        if [ -n "$_c" ]; then
            _outc=$_c
            break
        else
            for _i in ${_arg_list[@]}
            do
                _t=`echo $_i | grep -E "^$REPLY"`
                if [ -n "$_t" ]; then
                    _outc=$_i
                    break
                fi
            done
            if [ -n "$_outc" ]; then
                break
            fi
        fi
    done
    if [ -n "$_outc" ]; then
        eval "$_target_arg=$_outc"
        export "$_target_arg=$_outc"
    fi
}

function replace_config()
{
    eval "_value=\$$1"
    if [ -n "$_value" ]; then
        sed -i "s/^$1=[^=]*/$1=$_value/g" $BUILD_CONFIG_FILE
    fi
}

#mk_yunos.sh process begin
UKERNEL_TYPE=""
BUILD_CHIP=""
BUILD_PRODUCT=""
BUILD_STAGE=""
BUILD_STAGE_LIST=("EVB" "DVT" "others")
CONFIG_YUNIO_TYPE=""
CONFIG_YUNIO_TYPE_LIST=("ccp" "cmns")
CONFIG_YUNIO_ONLINE=y
CONFIG_TFS_ONLINE=y
CONFIG_CCP_ONLINE=y
CONFIG_DYSS_ONLINE=y
CONFIG_UKERNEL_TYPE=""

BUILD_DIR="$BASE/id.kernel"
BUILD_CONFIG_FILE="$BUILD_DIR/.config"
BOOTLOADER_DIR="id.boot/bootloader"
HW_CONFIG_TOP="id.kernel/hardware/id.bsp/configs"
BUILD_OUT="$BASE/out"
BOOTLOADER_MAKEARGS="V=5"

# auto detect ukernel type
# find all ukernel type from id.kernel/ukernel 
uknum=0;
for uk in `ls -l id.kernel/ukernel/ |awk '/^d/ {print $NF}'`
do
    if [ -z "$(echo $uk | grep '/')" ]; then  # filter folders
        UKERNEL_TYPE_LIST[$uknum]=$uk
        uknum=`expr $uknum + 1`
    fi
done

# auto detect chip name
# find all chip name from id.kernel/hardware/id.bsp/configs
chipnum=0
for chip in `ls -l id.kernel/hardware/id.bsp/configs/ |awk '/^d/ {print $NF}'`
do
    if [ -z "$(echo $chip | grep '/')" ]; then  # filter folders
        YUNOS_CHIP_NAME_LIST[$chipnum]=$chip
        chipnum=`expr $chipnum + 1`

    fi
done

build_config="$BASE/out/build/build.config"
mkdir -p `dirname $build_config`
[[ -e $build_config ]] && rm $build_config

build_info="$BASE/out/build/build.info"
[[ -e $build_info ]] && rm $build_info

_input_args=($*)
moreArgs=""
# check arg one by one
for _arg in ${_input_args[@]}
do
    p1=`echo "$_arg" | awk -F "=" '{print $1}'`
    p2=`echo "$_arg" | awk -F "=" '{print $2}'`

    if [ -z "$p2" ]; then
        case $p1 in
            ccp|cmns)
                CONFIG_YUNIO_TYPE="$p1"
                ;;
            EVB|DVT|others)
                    BUILD_STAGE="$p1"
                    ;;
            online|offline)
                if [ "$p1" = "online" ];then
                    CONFIG_YUNIO_ONLINE=y
                    CONFIG_TFS_ONLINE=y
                    CONFIG_CCP_ONLINE=y
                    CONFIG_DYSS_ONLINE=y
                else
                    CONFIG_YUNIO_ONLINE=n
                    CONFIG_TFS_ONLINE=n
                    CONFIG_CCP_ONLINE=n
                    CONFIG_DYSS_ONLINE=n
                fi
                ;;
            --*)
                moreArgs="$moreArgs $p1"
                ;;
            *)
                # auto detect ukernel type
                for uk_exsit in ${UKERNEL_TYPE_LIST[@]}
                do
                    if [  "$uk_exsit" = "$p1" ];then
                        UKERNEL_TYPE="$p1"
                        break
                    fi
                done

                # auto detect chip name
                for chip_exsit in ${YUNOS_CHIP_NAME_LIST[@]}
                do
                    if [  "$chip_exsit" = "$p1" ];then
                        BUILD_CHIP="$p1"
                        break
                    fi
                done

                pjnum=0
                for pj in `ls -l id.kernel/hardware/id.bsp/configs/${BUILD_CHIP}/ | awk '/^d/ {print $NF}'`
                do
                    if [ -z "$(echo $pj | grep '/')" ] && [ $pj != "common" ]; then
                        YUNOS_PROJECT_NAME_LIST[$pjnum]=$pj
                        pjnum=`expr $pjnum + 1`
                    fi
                done

                # auto detect project name
                for pj_exsit in ${YUNOS_PROJECT_NAME_LIST[@]}
                do
                    if [  "$pj_exsit" = "$p1" ];then
                        BUILD_PRODUCT="$p1"
                        break
                    fi
                done
                ;;
        esac
    else
        echo "$p1=$p2" >> $build_config
    fi
done

#if can not find ukernel type, input it
if [ "$UKERNEL_TYPE" == "" ]; then
    echo "ukernel type:"
    _inlist=(${UKERNEL_TYPE_LIST[@]})
    select_choice UKERNEL_TYPE
fi

#if can not find chip name, input it
if [ "$BUILD_CHIP" == "" ]; then
    echo "target chip name:"
    _inlist=(${YUNOS_CHIP_NAME_LIST[@]})
    select_choice BUILD_CHIP
fi

# auto detect project name
# find all project name from id.kernel/hardware/id.bsp/configs/$BUILD_CHIP
pjnum=0
for pj in `ls -l id.kernel/hardware/id.bsp/configs/$BUILD_CHIP | awk '/^d/ {print $NF}'`
do
    if [ -z "$(echo $pj | grep '/')" ] && [ $pj != "common" ]; then
        YUNOS_PROJECT_NAME_LIST[$pjnum]=$pj
        pjnum=`expr $pjnum + 1`
    fi
done

#if can not find project name, input it
if [ "$BUILD_PRODUCT" == "" ]; then
    echo "target product name:"
    _inlist=(${YUNOS_PROJECT_NAME_LIST[@]})
    select_choice BUILD_PRODUCT
fi

#if can not find product model, input it
if [ "$BUILD_STAGE" == "" ]; then
    echo "please choose build stage:"
    _inlist=(${BUILD_STAGE_LIST[@]})
    select_choice BUILD_STAGE
fi

#if can not find build type,input it
if [ "$CONFIG_YUNIO_TYPE" == "" ]; then
   echo "please choose build type:"
   _inlist=(${CONFIG_YUNIO_TYPE_LIST[@]})
   select_choice CONFIG_YUNIO_TYPE
fi

PRODUCT_OUT="${BUILD_OUT}/target/product/${BUILD_PRODUCT}"
case "$BUILD_STAGE" in
    DVT)
        BUILD_BOARD="${BUILD_PRODUCT}-dvt"
    ;;
    EVB)
        BUILD_BOARD="${BUILD_PRODUCT}-evb"
    ;;
    *)
    ;;
esac

echo "BUILD_PRODUCT=$BUILD_PRODUCT" >> $build_info
echo "BUILD_STAGE=$BUILD_STAGE" >> $build_info
echo "CONFIG_YUNIO_TYPE=$CONFIG_YUNIO_TYPE" >> $build_info
echo "UKERNEL_TYPE=$UKERNEL_TYPE" >> $build_info
echo "BUILD_CHIP=$BUILD_CHIP" >> $build_info
echo "PRODUCT_OUT=$PRODUCT_OUT" >> $build_info
echo "BUILD_BOARD=$BUILD_BOARD" >> $build_info
echo "HW_BSP_CONFIG=${HW_CONFIG_TOP}/${BUILD_CHIP}/${BUILD_PRODUCT}" >> $build_info
echo "HW_BSP_BOARD=${HW_CONFIG_TOP}/${BUILD_CHIP}/${BUILD_PRODUCT}/${BUILD_STAGE}" >> $build_info

function replace_kernel_config()
{
    replace_config CONFIG_YUNIO_TYPE     #update build type(ccp|cmns)
    replace_config CONFIG_YUNIO_ONLINE   #update online|offline(cmns|cpp)
    replace_config CONFIG_TFS_ONLINE     #update online|offline(cmns)
    replace_config CONFIG_CCP_ONLINE     #update online|offline(cpp)
    replace_config CONFIG_DYSS_ONLINE

    #for parameter is CONFIG_XXX=XXX and CONFIG_UKERNEL_TYPE
    while read LINE
    do
        item_name=`echo $LINE | awk -F "=" '{print $1}'`
        item_value=`echo $LINE | awk -F "=" '{print $2}'`
        if [[ $item_name == CONFIG_* ]]; then
            if [ -n "`cat $BUILD_CONFIG_FILE | grep ^${item_name}=`" ]; then
                eval $item_name=\"$item_value\"
                replace_config $item_name
            else
                echo "$LINE" >> $BUILD_CONFIG_FILE
            fi
        else
            echo "Error:$CONFIG_NAME not begin with CONFIG"
            exit -1
        fi
    done < $build_config
}

function build_kernel()
{
    local make_ret=1

    pushd $BUILD_DIR > /dev/null
    if [ $BUILD_STAGE == "others" ]; then
        cp -dpR hardware/id.bsp/configs/$BUILD_CHIP/$BUILD_PRODUCT/*  ./
    else
        cp -dpR hardware/id.bsp/configs/$BUILD_CHIP/$BUILD_PRODUCT/$BUILD_STAGE/*  ./
    fi

    # build ota update
    if [ -f hardware/id.bsp/configs/$BUILD_CHIP/$BUILD_PRODUCT/$BUILD_STAGE/otaconfig ]; then
        cp otaconfig .config
        rm -f ${PRODUCT_OUT}/*yunos*
        make "PRODUCT_OUT=$PRODUCT_OUT" clean
        make "PRODUCT_OUT=$PRODUCT_OUT"
        if [ $? = 0 ]; then
            pushd $PRODUCT_OUT
            rename 's/yunos/update/g' *yunos*
            find . -not \( -name '*update*' \) -delete
            popd
        fi
    fi

    mv defconfig  .config
    #save CONFIG_UKERNEL_TYPE for check
    echo "CONFIG_UKERNEL_TYPE=\"$UKERNEL_TYPE\"" >> "${build_config}"
    if [ "$UKERNEL_TYPE" != "pumpkin" ]; then
        replace_kernel_config
    fi

    make "PRODUCT_OUT=$PRODUCT_OUT" clean
    make "PRODUCT_OUT=$PRODUCT_OUT"
    make_ret=$?

    popd > /dev/null

    if [ $make_ret != 0 ]; then
        echo "ERROR: make kernel failed"
    fi
    return $make_ret
}

function build_bootloader()
{
    local make_ret=1

    pushd "$BOOTLOADER_DIR" > /dev/null
    make "$BOOTLOADER_MAKEARGS" "BUILD_BOARD=$BUILD_BOARD" "PRODUCT_OUT=$PRODUCT_OUT"
    make_ret=$?
    popd > /dev/null

    if [ $make_ret != 0 ]; then
        echo "ERROR: make bootloader failed"
    fi
    return $make_ret
}

#build
ret=1
while (true)
do
    export PATH=$(pwd)/build/toolchain/${BUILD_CHIP}/bin:$PATH
    if [ -z "$moreArgs" ] || [ $moreArgs = "--kernel" ]; then
        build_kernel
        [[ $? = 0 ]] || break
    fi

    BUILD_BOARD_CONFIG="id.boot/bootloader/boot/configs/${BUILD_BOARD}.cfg"
    if [ -f "$BUILD_BOARD_CONFIG" ]; then
        if [ -z "$moreArgs" ] || [ $moreArgs = "--bootloader" ]; then
            build_bootloader
            [[ $? = 0 ]] || break
        fi
    else
        echo "WARNING: no $BUILD_BOARD_CONFIG file to make bootloader for $BUILD_PRODUCT"
    fi

    imgout
    ret=0
    break
done

exit $ret
