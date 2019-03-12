############################################################################
# apps/system/evmanager/Makefile
#
#   Copyright (C) 2016 Xu Hang. All rights reserved.
#   Author: Xu Hang <xuhang@silan.com.cn>
#
############################################################################

-include $(TOPDIR)/.config
-include $(TOPDIR)/Make.defs
-include $(APPDIR)/Make.defs
-include $(TOPDIR)/../libs/libiuv/Make.defs

CFLAGS += -I$(APPDIR)/include
CFLAGS += -I$(TOPDIR)/include
#CFLAGS += -I$(TOPDIR)/../libs/libiuv/include
#CFLAGS += -I$(TOPDIR)/../ydk/include/id.js
#CFLAGS += -I$(TOPDIR)/../id.js/core/include
CFLAGS += -I$(APPDIR)/system/nxplayer
CFLAGS += -I$(APPDIR)/system/sl_lcd
CFLAGS += -I$(APPDIR)/system/airplay
#CFLAGS += -I$(APPDIR)/system/local_playlist
#CFLAGS += -I$(APPDIR)/system/evmanager
#CFLAGS += -I$(TOPDIR)/hardware/id.bsp/configs/$(CONFIG_ARCH_CHIP)/common/include
#CFLAGS += -I$(TOPDIR)/hardware/id.bsp/$(CONFIG_ARCH_CHIP)/include/common
CFLAGS += -I$(TOPDIR)/hardware/drivers/wireless/
CFLAGS += -I$(APPDIR)/system/fat32_filelist/
CFLAGS += -I$(APPDIR)/system/avs_uart/
ifeq ($(WINTOOL),y)
INCDIROPT = -w
endif

ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
UI_DIR = $(APPDIR)/system/sl_ui
ROMFS_DIR = $(UI_DIR)/romfs
ROMFS_IMG = $(UI_DIR)/romfs.img
ROMFS_HDR = $(UI_DIR)/romfs.h
endif
# Simulation Input

PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 16384

ASRCS =
CSRCS =
MAINSRC = sl_ui_main.c
CSRCS += sl_ui_main.c sl_ui_handle.c sl_ui_dialog.c sl_ui_cmd.c 
CSRCS += sl_ui_show.c sl_ui_table.c sl_ui_post.c sl_ui_action.c sl_sys.c sl_ui_event.c
ifeq ($(CONFIG_SC6138_ADC),y)
CSRCS += sl_adckey.c
endif

ifeq ($(CONFIG_FAT32_FILELIST),y)
CSRCS += sl_ui_local.c 
endif

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

SRCS = $(ASRCS) $(CSRCS)
OBJS = $(AOBJS) $(COBJS)

ifneq ($(CONFIG_BUILD_KERNEL),y)
  OBJS += $(MAINOBJ)
endif

ifeq ($(CONFIG_WINDOWS_NATIVE),y)
  BIN = ..\..\libapps$(LIBEXT)
else
ifeq ($(WINTOOL),y)
  BIN = ..\\..\\libapps$(LIBEXT)
else
  BIN = ../../libapps$(LIBEXT)
endif
endif

ifeq ($(WINTOOL),y)
  INSTALL_DIR = "${shell cygpath -w $(BIN_DIR)}"
else
  INSTALL_DIR = $(BIN_DIR)
endif

CONFIG_XYZ_PROGNAME ?= ui$(EXEEXT)
PROGNAME = $(CONFIG_XYZ_PROGNAME)

ROOTDEPPATH = --dep-path .

APPNAME = ui

# Common build

VPATH =

all: .built
.PHONY: context .depend depend clean distclean

$(AOBJS): %$(OBJEXT): %.S
	$(call ASSEMBLE, $<, $@)

$(COBJS) $(MAINOBJ): %$(OBJEXT): %.c
	$(call COMPILE, $<, $@)

ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
# Create the romfs.img file from the populated romfs directory

populate: $(ROMFS_DIR) $(ROMFS_DIR)/001.mp3  $(ROMFS_DIR)/002.mp3 $(ROMFS_DIR)/003.mp3 $(ROMFS_DIR)/004.mp3 $(ROMFS_DIR)/005.mp3

$(ROMFS_IMG): populate
	@genromfs -f $@ -d $(ROMFS_DIR) -V "FLASH_MUSIC_TEST"

# Create the romfs.h header file from the romfs.img file

$(ROMFS_HDR) : $(ROMFS_IMG)
	@(xxd -i romfs.img | sed -e "s/^unsigned/static const unsigned/g" >$@)
endif
ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
.built: $(ROMFS_HDR)  $(OBJS)
else
.built: $(OBJS)
endif
	$(call ARCHIVE, $(BIN), $(OBJS))
	$(Q) touch .built
	./mktone.sh
	install tone_data.bin $(PRODUCT_OUT)
	ls userspace.bin; \
	if [ $$? = 0 ];then \
	install userspace.bin $(PRODUCT_OUT);\
	fi

ifeq ($(CONFIG_BUILD_KERNEL),y)
$(BIN_DIR)$(DELIM)$(PROGNAME): $(OBJS) $(MAINOBJ)
	@echo "LD: $(PROGNAME)"
	$(Q) $(LD) $(LDELFFLAGS) $(LDLIBPATH) -o $(INSTALL_DIR)$(DELIM)$(PROGNAME) $(ARCHCRT0OBJ) $(MAINOBJ) $(LDLIBS)
	$(Q) $(NM) -u  $(INSTALL_DIR)$(DELIM)$(PROGNAME)

install: $(BIN_DIR)$(DELIM)$(PROGNAME)

else
install:

endif

# Register application

ifeq ($(CONFIG_NSH_BUILTIN_APPS),y)
$(BUILTIN_REGISTRY)$(DELIM)$(APPNAME)_main.bdat: $(DEPCONFIG) Makefile
	$(call REGISTER,$(APPNAME),$(PRIORITY),$(STACKSIZE),$(APPNAME)_main)

context: $(BUILTIN_REGISTRY)$(DELIM)$(APPNAME)_main.bdat
else
context:
endif

# Create dependencies

.depend: Makefile $(SRCS)
	$(Q) $(MKDEP) $(ROOTDEPPATH) "$(CC)" -- $(CFLAGS) -- $(SRCS) >Make.dep
	$(Q) touch $@

depend: .depend

clean:
ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
	$(call DELFILE$(ROMFS_HDR))
	$(call DELFILE, $(ROMFS_IMG))
endif
	$(call DELFILE, .built)
	$(call CLEAN)

distclean: clean
	$(call DELFILE, Make.dep)
	$(call DELFILE, .depend)

-include Make.dep
