#!/bin/sh 
# name1+name2+config
# looks like sc6138a-xj-2_DVT_config  
multiconfig=$1
echo $multiconfig

Intercept="_"
dir_Intercept="-"

dir1=${multiconfig%%$Intercept*}
dir2=${multiconfig##*$Intercept}
dir3=${multiconfig%$Intercept*}
dir4=${dir3##*$Intercept}
dir5=${dir1%%$dir_Intercept*}


seconddir=$dir1
thirddir=$dir4
firstdir=${multiconfig5}

echo $firstdir
echo $seconddir
echo $thirddir


Dirconfig="hardware/id.bsp/configs/"
FILE=/*
config_def="defconfig"

echo "search dir"
cd $Dirconfig
filelist=$(ls)
for dir in $filelist
do
	if [ -d $dir ]
	then
	echo $seconddir | grep $dir > /dev/null 2>&1 
	if [ $? -eq 0 ]; then
		 firstdir=$dir 
    		 echo $firstdir 
	fi 
	fi
done

cd $firstdir
cd $seconddir
cd $thirddir
cp ./* ../../../../../../
cd ../../../../../../
cp $config_def .config



