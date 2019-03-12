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
#CFLAGS += -I$(TOPDIR)/../libs/libiuv/include
#CFLAGS += -I$(TOPDIR)/../ydk/include/id.js
#CFLAGS += -I$(TOPDIR)/../id.js/core/include
#CFLAGS += -I$(APPDIR)/system/nxplayer
#CFLAGS += -I$(TOPDIR)/hardware/id.bsp/configs/$(CONFIG_ARCH_CHIP)/common/include
CFLAGS += -I$(TOPDIR)/hardware/id.bsp/$(CONFIG_ARCH_CHIP)/include/common
#CFLAGS += -I$(TOPDIR)/hardware/id.bsp/include/
ifeq ($(WINTOOL),y)
INCDIROPT = -w
endif

# Simulation Input

PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 4096

ASRCS =
CSRCS =
  CSRCS += sl_lcd_main.c sl_gb2312_unicode.c enfont_tbl.c
CSRCS += display_char.c font.c font_file.c mbcs.c unicode.c

MAINSRC = sl_lcd_main.c

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

CONFIG_XYZ_PROGNAME ?= lcd$(EXEEXT)
PROGNAME = $(CONFIG_XYZ_PROGNAME)

ROOTDEPPATH = --dep-path .

APPNAME = lcd

# Common build

VPATH =

all: .built
.PHONY: context .depend depend clean distclean

$(AOBJS): %$(OBJEXT): %.S
	$(call ASSEMBLE, $<, $@)

$(COBJS) $(MAINOBJ): %$(OBJEXT): %.c
	$(call COMPILE, $<, $@)


.built: $(OBJS)
	$(call ARCHIVE, $(BIN), $(OBJS))
	$(Q) touch .built
	install romfs/en16dst.fnt $(PRODUCT_OUT)
	install romfs/unicode_font.bin $(PRODUCT_OUT)
	install romfs/gb_unicode_map.bin $(PRODUCT_OUT)
	install romfs/gb_unicode_tbl.bin $(PRODUCT_OUT)

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
	$(call DELFILE, .built)
	$(call CLEAN)

distclean: clean
	$(call DELFILE, Make.dep)
	$(call DELFILE, .depend)

-include Make.dep
