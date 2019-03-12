#!/bin/bash

M0_LIMIT=$[256*1024]
CK_LIMIT=$[4096*1024]

config_path=`find ../ -name .config`
have_dsp=$(cat $config_path | grep "^CONFIG_SILAN_DSP=" | awk -F '=' '{print $NF}')
if [ "$have_dsp" = "y" ];
then
m0_bin=ck_dsp_boot_0x1c0000-200m.bin
echo "use 200m m0 boot!!!"
else
m0_bin=ck_dsp_boot_0x1c0000-120m.bin
echo "use 160m m0 boot!!!"
fi
m0_path=`find ../out -name $m0_bin`
echo "$m0_path"
cp $m0_path .

m0_insize=`stat -c%s $m0_bin`
ck_insize=`stat -c%s program_final.binary`

if [ $m0_insize -gt $M0_LIMIT ];
then
	echo "m0 boot size is too large!"
	exit 1
fi

if [ $ck_insize -gt $CK_LIMIT ];
then
	echo "ck size is too large!"
	exit 1
fi

#	dsp hifi3 assemble code for jump to 0x2400000
#	__begin: 0x02400000
#	l32r	a2, __begin
#	jx		l32r
echo 0000400221ffffa00200 | xxd -r -ps > jump.hex
dd if=$m0_bin					bs=1024	skip=0	seek=0			count=1		of=flash_ap.bin 
dd if=program_final.binary		bs=1024	skip=0	seek=1			count=1		of=flash_ap.bin	
dd if=jump.hex					bs=4	skip=0	seek=511		count=3		of=flash_ap.bin
dd if=$m0_bin					bs=1024	skip=0	seek=4			count=124	of=flash_ap.bin
dd if=program_final.binary		bs=1024	skip=0	seek=128		count=4096	of=flash_ap.bin
rm jump.hex
