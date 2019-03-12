
cd ../
KCONFIG_DIR=$PWD/Kconfig_tool/
KCONFIG_TOOL_DIR=$KCONFIG_DIR/install_tool
KCONFIG_NCURSES_DIR=$KCONFIG_DIR/install_ncu
if [ ! -d $KCONFIG_DIR ] ;then
        mkdir $KCONFIG_DIR
	if [ ! -d $KCONFIG_TOOL_DIR ] ;then
        mkdir $KCONFIG_TOOL_DIR
        fi
	if [ ! -d $KCONFIG_NCURSES_DIR ] ;then
	mkdir $KCONFIG_NCURSES_DIR
	fi
	
fi
OUTTA=$(find  $KCONFIG_DIR/ -maxdepth 1 -name 'kconfig-*')
#echo OUTTA=$OUTTA
echo $OUTTA |  grep "kconfig-mconf" > /dev/null 2>&1
if [ $? -eq 0 ]; then
        echo "HOST HAVE INSTALL kconfig"
        exit 0
fi
cd id.kernel/tools
KCONFIG_ZIP_DIR=$PWD/Kconfig_zip/
if [ ! -d $KCONFIG_ZIP_DIR ] ;then
        echo "ERROR 0 can't find the source of code, please install it from codebase"
        exit 1
fi
cd $KCONFIG_ZIP_DIR
#KCONFIG_DIR=$PWD/install
OUTA=$(find /usr/include/ -name curses.h)
echo $OUTA | grep "curses.h" > /dev/null 2>&1
if [ $? -eq 0 ]; then
        OUTB=$(find /usr/include/ -name ncurses.h)
        echo $OUTB | grep "ncurses.h" > /dev/null 2>&1
        if [ $? -eq 0 ] ;then
                echo "HOST HAVE INSTALL ncurses"
                tar  -jxvf kconfig-frontends-3.12.0.0.tar.bz2
                NCURSES=0
        fi
else
        echo "HOST NEED INSTALL ncurses"
        tar -jxvf kconfig-frontends-3.12.0.0.tar.bz2
        tar -xzvf ncurses-6.0.tar.gz
        cd ncurses-6.0
        mkdir install
        OUTC=$PWD
        ./configure --prefix=$KCONFIG_NCURSES_DIR
        OUTD=$(find -maxdepth 1 -name Makefile)
        echo $OUTD
        echo $OUTD | grep "Makefile" > /dev/null 2>&1
        if [ $? -ne 0 ]; then
                echo "ERROR 1 configure failed can't auto install ncurses,please install by yourself"
                exit 1
        fi
        make
        make install
#       make distclean
        cd $KCONFIG_NCURSES_DIR
        NCURSEIS_DIR=$PWD
        cd lib
        NCURSEIS_LIB_DIR=$PWD
        cd ../include/ncurses/
        if [ $? -ne 0 ]; then
                echo "ERROR 2 make failed can't auto install ncurses,please install by yourself"
        fi
        echo now1 dir=$PWD
        cp -r ./* ../
        cd ..
        NCURSEIS_INCLUDE_DIR=$PWD #get dir 
        cd ../../../
        NCURSES=1
        pwd
fi
echo "HOST INSTALL menuconfig"
cd $KCONFIG_ZIP_DIR
cd kconfig-frontends-3.12.0.0
if [ ! -d "install" ] ;then
	mkdir install
fi

echo NCURSEIS_INCLUDE_DIR=$NCURSEIS_INCLUDE_DIR 
#exit 1
if [ $NCURSES -eq 1 ];then
        ./configure --prefix=$KCONFIG_TOOL_DIR CPPFLAGS=-I$NCURSEIS_INCLUDE_DIR LDFLAGS=-L$NCURSEIS_LIB_DIR --enable-mconf --enable-static
	echo ./configure --prefix=$KCONFIG_TOOL_DIR CPPFLAGS=-I$NCURSEIS_INCLUDE_DIR LDFLAGS=-L$NCURSEIS_LIB_DIR --enable-mconf --enable-static
else
        ./configure --prefix=$KCONFIG_TOOL_DIR --enable-mconf --enable-static
	echo ./configure --prefix=$KCONFIG_TOOL_DIR --enable-mconf --enable-static
fi
                                                                                                                                                                                                                                                                    
OUTDD=$(find -maxdepth 1 -name Makefile)
echo $OUTDD
echo $OUTDD | grep "Makefile" > /dev/null 2>&1
if [ $? -ne 0 ]; then
        echo "ERROR 4 configure failed can't auto install menuconfig,please install by yourself"
        exit 1
fi
make
make install
#make distclean
cd $KCONFIG_TOOL_DIR
OUTDD=$(find -maxdepth 2 -name kconfig-*)
echo $OUTDD
echo $OUTDD | grep "kconfig-mconf" > /dev/null 2>&1
if [ $? -ne 0 ]; then
        echo "ERROR 5 make failed can't auto install menuconfig,please install by yourself"
        exit 1
fi
                                                                                                                                                                                                                                                                    
cp bin/* $KCONFIG_DIR
cd $KCONFIG_ZIP_DIR
echo "delete all file while is appending"
pwd
ls

if [ -d "ncurses-6.0" ] ;then
rm -r ncurses-6.0 
fi
if [ -d "kconfig-frontends-3.12.0.0" ] ;then
rm -r kconfig-frontends-3.12.0.0
fi
