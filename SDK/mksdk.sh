#!/bin/sh
echo 'try make zhuque sdk!'
cp -r yoc zhuque
rm -r ./zhuque/build/.git
rm -r ./zhuque/cloudcard/.git
rm -r ./zhuque/deps/.git
rm -r ./zhuque/id.boot/bootrom/.git
rm -r ./zhuque/id.boot/imgmk/.git
rm -r ./zhuque/id.boot/bootloader/.git
rm -r ./zhuque/id.ivt/.git
rm -r ./zhuque/id.js/.git
rm -r ./zhuque/id.kernel/.git
rm -r ./zhuque/id.kernel/ukernel/lemon
rm -r ./zhuque/id.kernel/ukernel/pumpkin
rm -r ./zhuque/id.mvm/.git
rm -r ./zhuque/id.tfs/.git
rm -r ./zhuque/libs/libinetutils/.git
rm -r ./zhuque/libs/libopus/.git
rm -r ./zhuque/libs/libiuv/.git
rm -r ./zhuque/libs/libc/.git
rm -r ./zhuque/libs/crypto/.git
rm -r ./zhuque/ydk/.git
rm -r ./zhuque/id.boot
touch ./zhuque/nuttx_module
rm -r ./zhuque/nuttx_module
rm -rf ./zhuque/.repo/

sed -i 's/yunos/zhuque/g' ./zhuque/id.kernel/Makefile.unix
sed -i 's/nuttx/zhuque/g' ./zhuque/build/tools/mk_ima.sh
sed -i 's/yunos/zhuque/g' ./zhuque/id.kernel/ukernel/banana/arch/csky/src/Makefile
sed -i 's/yunos/zhuque/g' ./zhuque/id.kernel/ukernel/banana/arch/csky/src/compressed/Makefile

echo 'sdk make success!'

