############################################################################
# FlatLibs.mk
#
#   Copyright (C) 2007-2012, 2014 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

# NUTTXLIBS is the list of NuttX libraries that is passed to the
#   processor-specific Makefile to build the final NuttX target.
#   Libraries in FSDIRS are excluded if file descriptor support
#   is disabled.
# USERLIBS is the list of libraries used to build the final user-space
#   application
# EXPORTLIBS is the list of libraries that should be exported by
#   'make export' is

NUTTXLIBS = libsched$(LIBEXT)
USERLIBS =

# Add libraries for board support

NUTTXLIBS += libconfigs$(LIBEXT)

NUTTXLIBS += libinit$(LIBEXT)

ifeq ($(CONFIG_IDTFS_CRYPTO), y)
#NUTTXLIBS += libtfscrypto$(LIBEXT)
endif

ifeq ($(CONFIG_MONITOR),y)
#NUTTXLIBS += libmonitor$(LIBEXT)
endif

ifeq ($(CONFIG_SECURITY_IMA),y)
NUTTXLIBS += libyocsm$(LIBEXT)
else
ifeq ($(CONFIG_SECURITY_IDMAC),y)
NUTTXLIBS += libyocsm$(LIBEXT)
endif
endif

# Add libraries for syscall support.

NUTTXLIBS += libc$(LIBEXT) libmm$(LIBEXT)
NUTTXLIBS += libarch$(LIBEXT)
ifeq ($(CONFIG_CHIP_NAME),sc6138)
NUTTXLIBS += libdsp$(LIBEXT)

ifeq ($(CONFIG_SILAN_USBHS),y)
#NUTTXLIBS += libusb$(LIBEXT)
endif
endif

ifeq ($(CONFIG_CHIP_NAME),ap1508)
NUTTXLIBS += libdsp$(LIBEXT)
endif

ifeq ($(CONFIG_LIB_MEDIA),y)
#NUTTXLIBS += libmediainfo$(LIBEXT)
endif

ifeq ($(CONFIG_SILAN_SD),y)
#NUTTXLIBS += libsdmmc$(LIBEXT)
endif

ifeq ($(CONFIG_MAC_MONITOR),y)
ifeq ($(CONFIG_CHIP_SC6138),y)
NUTTXLIBS += libgmac$(LIBEXT)
endif
endif

ifeq ($(CONFIG_SYSTEM_UART1),y)
NUTTXLIBS += libhsuart$(LIBEXT)
endif

ifeq ($(CONFIG_SILAN_SPI_CTRL),y)
#NUTTXLIBS += libspi$(LIBEXT)
endif

ifeq ($(CONFIG_SDIO_DMA),y)
#NUTTXLIBS += libdma$(LIBEXT)
endif

ifeq ($(CONFIG_SSV),y)
NUTTXLIBS += lib_ssv_wifi$(LIBEXT)
endif

ifeq ($(CONFIG_LIB_SYSCALL),y)
NUTTXLIBS += libstubs$(LIBEXT)
USERLIBS  += libproxies$(LIBEXT)
endif

# Add libraries for C++ support.  CXX, CXXFLAGS, and COMPILEXX must
# be defined in Make.defs for this to work!

ifeq ($(CONFIG_HAVE_CXX),y)
NUTTXLIBS += libcxx$(LIBEXT)
endif

# Add library for application support.

ifneq ($(APPDIR),)
NUTTXLIBS += libapps$(LIBEXT)
endif

ifeq ($(CONFIG_CHIP_NAME),sc6138)

#This is YOC build lib list
#path macro is defined in Makfile.unix
-include CoreLibs.mk
NUTTXLIBS += $(CORELIBS)

ifneq ($(YOCLIBOPUSDIR),)
NUTTXLIBS += libopus$(LIBEXT)
endif

#ifneq ($(YOCLIBCRYPTO_MBEDTLS),)
#NUTTXLIBS += libmbedcrypto$(LIBEXT)
#endif

ifneq ($(YOCLIBCUNIT),)
NUTTXLIBS += libcunit$(LIBEXT)
endif

ifneq ($(YOCLIBYTEST),)
NUTTXLIBS += libytest$(LIBEXT)
endif

ifneq ($(IDMVMDIR),)
    ifeq ($(CONFIG_ARCH_SMARTDEVICE_P1),y)
        NUTTXLIBS += libmvm$(LIBEXT)
    endif
endif

ifneq ($(IDIVTDIR),)
NUTTXLIBS += libivt$(LIBEXT)
endif

#ifneq ($(IDJSDIR),)
#NUTTXLIBS += libidjs$(LIBEXT)
#ifeq ($(CONFIG_YUNIO_TYPE),cmns)
#NUTTXLIBS += libdevice_transport$(LIBEXT)
#endif
#NUTTXLIBS += libdevice_ota$(LIBEXT)
#NUTTXLIBS += libdevice_time_calibration$(LIBEXT)
#NUTTXLIBS += libdyss$(LIBEXT)
#ifeq ($(CONFIG_XIAOYUN),y)
#NUTTXLIBS += libxiaoyun$(LIBEXT)
#endif
#NUTTXLIBS += libmedia$(LIBEXT)
#NUTTXLIBS += libyunio$(LIBEXT)
#endif

ifneq ($(IDTFSDIR),)
#NUTTXLIBS += libtfshal$(LIBEXT)
endif

else

ifeq ($(CONFIG_CHIP_NAME),ap1508)
#This is YOC build lib list
#path macro is defined in Makfile.unix
-include CoreLibs.mk
NUTTXLIBS += $(CORELIBS)

ifneq ($(YOCLIBOPUSDIR),)
NUTTXLIBS += libopus$(LIBEXT)
endif

#ifneq ($(YOCLIBCRYPTO_MBEDTLS),)
#NUTTXLIBS += libmbedcrypto$(LIBEXT)
#endif

ifneq ($(YOCLIBCUNIT),)
NUTTXLIBS += libcunit$(LIBEXT)
endif

ifneq ($(YOCLIBYTEST),)
NUTTXLIBS += libytest$(LIBEXT)
endif

ifneq ($(IDMVMDIR),)
    ifeq ($(CONFIG_ARCH_SMARTDEVICE_P1),y)
        NUTTXLIBS += libmvm$(LIBEXT)
    endif
endif

ifneq ($(IDIVTDIR),)
NUTTXLIBS += libivt$(LIBEXT)
endif

ifneq ($(IDTFSDIR),)
#NUTTXLIBS += libtfshal$(LIBEXT)
endif

else

ifeq ($(CONFIG_CHIP_NAME),hobbit)
#This is YOC build lib list
#path macro is defined in Makfile.unix
-include CoreLibs.mk
NUTTXLIBS += $(CORELIBS)
endif
endif

endif
# Add libraries for network support

ifeq ($(CONFIG_NET_LWIP),y)
NUTTXLIBS += libnet$(LIBEXT)
endif

# Add libraries for Crypto API support

ifeq ($(CONFIG_CRYPTO),y)
NUTTXLIBS += libcrypto$(LIBEXT)
endif

# Add libraries for file system support

ifeq ($(CONFIG_NFILE_DESCRIPTORS),0)
ifneq ($(CONFIG_NSOCKET_DESCRIPTORS),0)
NUTTXLIBS += libfs$(LIBEXT)
endif
ifeq ($(CONFIG_NET),y)
NUTTXLIBS += libdrivers$(LIBEXT)
endif
else
ifeq ($(CONFIG_UKERNEL_TYPE), banana)
NUTTXLIBS += libfs$(LIBEXT) libdrivers$(LIBEXT) libbinfmt$(LIBEXT)
else
NUTTXLIBS += libfs$(LIBEXT) libdrivers$(LIBEXT)
endif
endif

# Add libraries for the NX graphics sub-system

ifeq ($(CONFIG_NX),y)
NUTTXLIBS += libgraphics$(LIBEXT)
NUTTXLIBS += libnx$(LIBEXT)
endif

# Add libraries for the Audio sub-system

ifeq ($(CONFIG_AUDIO),y)
#NUTTXLIBS += libaudio$(LIBEXT)
endif

# Add libraries for the libtuv

ifeq ($(CONFIG_LIB_TUV_EXTERNAL),y)
NUTTXLIBS += libtuv$(LIBEXT)
endif
ifeq ($(CONFIG_LIB_TUVTESTER_EXTERNAL),y)
NUTTXLIBS += libtuvtester$(LIBEXT)
endif

# Add libraries for the Broadcom wifi libmhd

ifeq ($(CONFIG_BCM_WIFI),y)
NUTTXLIBS += libmhd$(LIBEXT)
endif

# Add libraries for the bluetooth

ifeq ($(CONFIG_BLUETOOTH),y)
NUTTXLIBS += libbt$(LIBEXT)
endif

# Add libraries for DMR

ifeq ($(CONFIG_SYSTEM_DMR),y)
NUTTXLIBS += libdmr$(LIBEXT)
endif

# Add libraries for airPlay

ifeq ($(CONFIG_SYSTEM_AIRPLAY),y)
NUTTXLIBS += libshairport$(LIBEXT)
endif

# Add libraries for id.bsp common
NUTTXLIBS += libbspcommon$(LIBEXT)

# Add libraries for id.hal 
NUTTXLIBS += libhal$(LIBEXT)

# Add libraries for alink 
ifeq ($(CONFIG_WIFI_ALSETUP),y)
NUTTXLIBS += libaws$(LIBEXT)
endif

ifeq ($(CONFIG_DECOMPRESS), y)
NUTTXLIBS += libdecompress$(LIBEXT)
endif

ifeq ($(CONFIG_NGHTTP2), y)
NUTTXLIBS += libnghttp2$(LIBEXT)
endif

ifeq ($(CONFIG_YOC_RHINO), y)
NUTTXLIBS += librhino$(LIBEXT)
endif

ifeq ($(CONFIG_FAT32_FILELIST), y)
#NUTTXLIBS += libfat32list$(LIBEXT)
endif

ifeq ($(CONFIG_CEC), y)
#NUTTXLIBS += libcec$(LIBEXT)
endif
# Export all libraries

ifeq ($(CONFIG_SOFTDECODE), y)
NUTTXLIBS +=  libdaac$(LIBEXT)
endif

EXPORTLIBS = $(NUTTXLIBS)
