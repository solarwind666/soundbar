#!/bin/bash

export PATH=$(pwd)/build/toolchain/bin:$PATH

function make_images()
{
    local ret=1
    local cpucores=$(cat /proc/cpuinfo | grep processor | wc -l)

    pushd id.kernel > /dev/null
    cp -dpR ./hardware/id.bsp/configs/sc6138a-xj-1/nsh/*  ./
    mv defconfig  .config
    local cpucores=$(cat /proc/cpuinfo | grep processor | wc -l)
    #make -j $cpucores $@
    make
    ret=$?
    popd > /dev/null

    if [ $ret = 0 ]; then
        echo "INFO: make $@ completed successfully"
    else
        echo "ERROR: make $@ completed failed"
    fi
    return $ret
}

make_images "$@"
exit $?
