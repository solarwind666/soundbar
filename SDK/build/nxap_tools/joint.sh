#!/bin/bash

#joint chinese font lib 
RELEASE_IMAGE=release-images
gcc -o ${RELEASE_IMAGE}/add_user_data build/nxap_tools/tools/src/add_user_data.c
BUILD_TO_INFO=out/build/build.info
echo ${BUILD_TO_INFO}
PRODUCT_OUT=`cat ${BUILD_TO_INFO} | grep ^PRODUCT_OUT | awk -F "=" '{print $NF}'`
echo ${PRODUCT_OUT}
cp ${PRODUCT_OUT}/wifi_firmware.bin ${RELEASE_IMAGE}/
cp ${PRODUCT_OUT}/userspace.bin ${RELEASE_IMAGE}/
cp ${PRODUCT_OUT}/sysdata.bin ${RELEASE_IMAGE}/
cp ${PRODUCT_OUT}/unicode_font.bin ${RELEASE_IMAGE}/
cp ${PRODUCT_OUT}/gb_unicode_map.bin ${RELEASE_IMAGE}/
cp ${PRODUCT_OUT}/gb_unicode_tbl.bin ${RELEASE_IMAGE}/
ELF_PATH=${PRODUCT_OUT}/zhuque
BOOT_ADDR=`grep -ar -m1 -z "boot," ${ELF_PATH}`
BTCONF_ADDR=`grep -ar -m1 -z "btconf," ${ELF_PATH}`
IMAGE_ADDR=`grep -ar -m1 -z "image2," ${ELF_PATH}`
TONE_ADDR=`grep -ar -m1 -z "tonespace," ${ELF_PATH}`
CH_FNT_ADDR=`grep -ar -m1 -z "chfnt," ${ELF_PATH}`
TBL_ADDR=`grep -ar -m1 -z "table," ${ELF_PATH}`
USER_ADDR=`grep -ar -m1 -z "userspace," ${ELF_PATH}`
WIFI_ADDR=`grep -ar -m1 -z "wifibin," ${ELF_PATH}`
SYSDATA_ADDR=`grep -ar -m1 -z "sysdata," ${ELF_PATH}`

TBL_PATH=`find . -name sl_lcd.h`
GB_UNICODE_MAP_OFFSET=`grep -nr "GB_UNICODE_MAP_OFFSET" ${TBL_PATH} | awk -F ' ' '{print $NF}'`
GB_UNICODE_TBL_OFFSET=`grep -nr "GB_UNICODE_TBL_OFFSET" ${TBL_PATH} | awk -F ' ' '{print $NF}'`
echo ${ELF_PATH}
echo ${SYSDATA_ADDR}
echo ${WIFI_ADDR}
echo ${USER_ADDR}
echo ${TBL_PATH}
echo ${TBL_ADDR}
echo ${TONE_ADDR}
echo ${CH_FNT_ADDR}

pushd ${RELEASE_IMAGE}
./add_user_data "${BOOT_ADDR}" "${BTCONF_ADDR}" "${IMAGE_ADDR}" "${TONE_ADDR}" "${CH_FNT_ADDR}" "${TBL_ADDR}" "${USER_ADDR}" "${SYSDATA_ADDR}" "${WIFI_ADDR}" "${GB_UNICODE_MAP_OFFSET}" "${GB_UNICODE_TBL_OFFSET}" 
popd
