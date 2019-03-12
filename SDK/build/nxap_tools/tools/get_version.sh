#!/bin/bash
source ./input/script.cfg
FILEADDR=`${CROSS_TOOL}readelf -l $IMAGE1|grep LOAD|head -1|awk '{print $2}'`
LOADADDR=`${CROSS_TOOL}readelf -l $IMAGE1|grep LOAD|head -1|awk '{print $3}'`
KEYADDR=$((16#`${CROSS_TOOL}readelf -s $IMAGE1|grep g_sys_ver|head -1|awk '{print $2}'`))
SIZE=`${CROSS_TOOL}readelf -s $IMAGE1|grep g_sys_ver|head -1|awk '{print $3}'`
OFFSET=$(($KEYADDR-$LOADADDR+$FILEADDR))
dd if=$IMAGE1 of=system.ver skip=$OFFSET bs=1 count=$(($SIZE-1))
KEYADDR=$((16#`${CROSS_TOOL}readelf -s $IMAGE1|grep g_product_type|head -1|awk '{print $2}'`))
SIZE=`${CROSS_TOOL}readelf -s $IMAGE1|grep g_product_type|head -1|awk '{print $3}'`
OFFSET=$(($KEYADDR-$LOADADDR+$FILEADDR))
dd if=$IMAGE1 of=product.ver skip=$OFFSET bs=1 count=$(($SIZE-1))
KEYADDR=$((16#`${CROSS_TOOL}readelf -s $IMAGE1|grep g_sdk_level|head -1|awk '{print $2}'`))
SIZE=`${CROSS_TOOL}readelf -s $IMAGE1|grep g_sdk_level|head -1|awk '{print $3}'`
OFFSET=$(($KEYADDR-$LOADADDR+$FILEADDR))
dd if=$IMAGE1 of=sdk_level.ver skip=$OFFSET bs=1 count=$(($SIZE-1))
