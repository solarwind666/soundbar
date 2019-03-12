#########################################################################
#	Copyright 2008-2010, HangZhou SILAN MicroElectronics CO. , LTD		#
#	All rights reserved													#
#																		#
#	FileName:	compiler.mk												#
#	Author:		DongDongsheng													#
#	Created:	2008-7-23												#
#	Function:															#
#	Note:																#
#	History:															#
#########################################################################
MAKE  = make
AS    = $(TOOLCHAIN_PATH)as
CC    = $(TOOLCHAIN_PATH)gcc
CXX   = $(TOOLCHAIN_PATH)g++
LD    = $(TOOLCHAIN_PATH)ld
CONV	= $(TOOLCHAIN_PATH)conv
SIZE	= $(TOOLCHAIN_PATH)size
STRIP	= $(TOOLCHAIN_PATH)strip
OBJCOPY	= $(TOOLCHAIN_PATH)objcopy
OBJDUMP	= $(TOOLCHAIN_PATH)objdump
NM		= $(TOOLCHAIN_PATH)nm
READELF	= $(TOOLCHAIN_PATH)readelf
AR		= $(TOOLCHAIN_PATH)ar
STRIP	= $(TOOLCHAIN_PATH)strip

LIB_PATH = .

CC_PARAM += -fno-builtin -DCONFIG_CKCPU_MMU -mdsp -Os -ffunction-sections -fdata-sections -Wall -Wstrict-prototypes -Wshadow -Wundef -g  -fno-strict-aliasing -fno-strength-reduce #-I. -isystem # -pipe -g -D__NUTTX__ -DNDEBUG

LD_PARAM += -EL

#LD_LIB_PARAM = -lboard  -lgcc
#LD_LIB_PARAM += -lsched -lconfigs -linit -ltfscrypto -lmonitor -lyocsm -lc -lmm -larch -ldsp -lusb -lsdmmc -lgmac -lhsuart -lspi -ldma -lcxx
#LD_LIB_PARAM += -liuv -linetutils -lidjs -ldevice_transport -ldevice_ota -ldevice_time_calibration -lxiaoyun -lyunio -lmedia -lid2 -lmbedcrypto -lopus -lcunit -lytest -livt -ltfshal -lnet -lcrypto -lfs -ldrivers -lbinfmt -laudio
#LD_LIB_PARAM += -lbspcommon -lhal -ldecompress -lboard  -lgcc


#%.oo:%.cxx
#	$(CXX) $(CXXFLAGS) -o $@ -c $<
#
#%.o:%.c
#	$(CC) $(CC_PARAM) $(CFLAGS) -o $@ -c $<
#
#.S.o:
#	$(CC) $(CC_PARAM) $(CFLAGS) -o $@ -c $<
#
#.s.o:
#	$(CC) $(CC_PARAM) $(CFLAGS) -o $@ -c $<
#
#
