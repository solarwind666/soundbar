#!/bin/sh
rm -f tone_data.bin
rm -f tone_data.tmp
off=0
echo '#define __TONE_DAT_H__' >> tone_data.tmp
echo 'struct tone_data { uint32_t off; uint32_t size; };' >> tone_data.tmp
echo 'static struct tone_data datas[] = {' >> tone_data.tmp
for fn in $(grep 'file:tones' tone_data.h |sed 's/^.*file://'|sed 's/\s.*$//');
do
	sz=$(ls -l $fn | awk '{print $5}')
	echo "    { $off, $sz }," >> tone_data.tmp
	off=$(( $off + $sz ))
	cat $fn >> tone_data.bin;
done
echo '};' >> tone_data.tmp

