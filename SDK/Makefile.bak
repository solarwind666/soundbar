PRODUCT_NAME =
PRODUCT_OBJECT = mxk_main.o mxk_common_handle.o
SDK_PATH = SDK
CP_PATH = zhuque
ELF_NAME = zhuque
CUR_PATH = $(shell pwd)
CUR_LIB = $(CUR_PATH)/lib
#CUR_OBJ = $(CUR_PATH)/obj
USER_SRC_PATH = $(CUR_PATH)/src
USER_INC_PATH = $(CUR_PATH)/include
TOP_PATH = $(CUR_PATH)/../$(CP_PATH)
KERNEL_PATH = $(TOP_PATH)/id.kernel
CLOUD_PATH = $(TOP_PATH)/cloudcard
EXCLUDE_FILE = 
EXAMPLE_PATH = $(TOP_PATH)/cloudcard/examples
KERNEL_INC_PATH = $(KERNEL_PATH)/include
ARCH_PATH = $(KERNEL_PATH)/arch/csky/src
BSP_INC_PATH = $(KERNEL_PATH)/hardware/id.bsp/include
#IDJS_INC_PATH = $(KERNEL_PATH)/../id.js/core/include
#UV_INC_PATH = $(KERNEL_PATH)/../libs/libiuv/include
#UV_NUTTX_INC_PATH = $(KERNEL_PATH)/../libs/libiuv/source/nuttx/
#WIRELESS_PATH = $(KERNEL_PATH)/hardware/drivers/wireless
EXTERN_INCLUDE_PATH = $(USER_INC_PATH)/sl_include
OBJ_RELATION = $(CUR_PATH)/obj_relation
LIB_RELATION = $(CUR_PATH)/lib_relation
OBJ_COUNT = $(CUR_PATH)/obj_count

CONFIG_FROM_PATH = $(KERNEL_PATH)/.config
CONFIG_TO_PATH = $(CUR_PATH)/kernel/.config
MAKEDEFS_FROM_PATH = $(KERNEL_PATH)/Make.defs
MAKEDEFS_TO_PATH = $(CUR_PATH)/kernel/Make.defs
KERNELTOOLS_FROM_PATH = $(KERNEL_PATH)/tools
KERNELTOOLS_TO_PATH = $(CUR_PATH)/kernel/tools
BUILD_TO_PATH = $(CUR_PATH)/build
UPDATE_TOOL=mk_nuttx_part_head
BUILD_FROM_INFO = $(KERNEL_PATH)/../out/build/build.info
BUILD_TO_INFO = $(CUR_PATH)/out/build/build.info

WIFI_BIN_NAME = wifi_firmware.bin
LIB_APP_NAME = libapps.a
#LIB_APP_LINK_NAME = apps
#LIB_SCHE_NAME = libsched.a
RM = rm -rf
CP = cp -rf
MKDIR = mkdir

ifeq ($(BUILD_FROM_INFO), $(wildcard $(BUILD_FROM_INFO)))
BUILD_PRODUCT = $(shell cat $(BUILD_FROM_INFO) | grep ^BUILD_PRODUCT | awk -F "=" '{print $$NF}')
PRODUCTOUT_FROM_PATH=$(shell cat $(BUILD_FROM_INFO) | grep ^PRODUCT_OUT | awk -F "=" '{print $$NF}')
HW_BSP_CONFIG_FROM_PATH=$(shell cat $(BUILD_FROM_INFO) | grep ^HW_BSP_CONFIG | awk -F "=" '{print $$NF}')
#HW_BSP_BOARD_FROM_PATH=$(shell cat $(BUILD_FROM_INFO) | grep ^HW_BSP_BOARD | awk -F "=" '{print $$NF}')
endif

ifeq ($(BUILD_TO_INFO), $(wildcard $(BUILD_TO_INFO)))
BUILD_PRODUCT = $(shell cat $(BUILD_TO_INFO) | grep ^BUILD_PRODUCT | awk -F "=" '{print $$NF}')
$(shell sed -i "s/$(CP_PATH)/$(SDK_PATH)/g" $(BUILD_TO_INFO))
$(shell sed -i "8c HW_BSP_CONFIG=$(BUILD_PRODUCT)" $(BUILD_TO_INFO))
$(shell sed -i "9c HW_BSP_BOARD=$(BUILD_PRODUCT)/DVT" $(BUILD_TO_INFO))
PRODUCTOUT_TO_PATH=$(shell cat $(BUILD_TO_INFO) | grep ^PRODUCT_OUT | awk -F "=" '{print $$NF}')
PATH_MOD=$(shell cat $(BUILD_TO_INFO) | grep ^PRODUCT_OUT | awk -F "out/" '{print $$NF}')
PATH_MOD1="PRODUCT_OUT=$(CUR_PATH)/out/$(PATH_MOD)"
$(shell sed -i "6c $(PATH_MOD1)" $(BUILD_TO_INFO))
endif

ifeq ($(CONFIG_TO_PATH), $(wildcard $(CONFIG_TO_PATH)))
-include $(CONFIG_TO_PATH)
else 
ifeq ($(CONFIG_FROM_PATH), $(wildcard $(CONFIG_FROM_PATH)))
-include $(CONFIG_FROM_PATH)
endif
endif

include compiler.mk
include $(USER_SRC_PATH)/main.mk
include $(USER_SRC_PATH)/examples.mk

CONFIG_UKERNEL_TYPE := $(patsubst "%",%,$(strip $(CONFIG_UKERNEL_TYPE)))
CONFIG_ARCH       := $(patsubst "%",%,$(strip $(CONFIG_ARCH)))
CONFIG_ARCH_FAMILY := $(patsubst "%",%,$(strip $(CONFIG_ARCH_FAMILY)))
CONFIG_ARCH_CHIP  := $(patsubst "%",%,$(strip $(CONFIG_ARCH_CHIP)))
CONFIG_ARCH_BOARD := $(patsubst "%",%,$(strip $(CONFIG_ARCH_BOARD)))
CONFIG_CHIP_NAME := $(patsubst "%",%,$(strip $(CONFIG_CHIP_NAME)))


ifeq ($(CONFIG_CHIP_NAME), sc6138)
EXTRACT_SYS_IN_PATH = $(foreach tmp, $(EXTRACT_SYS_IN_SRC), $(shell find $(TOP_PATH) -name $(tmp) | grep -v "ap1508"))
$(warning $(EXTRACT_SYS_IN_PATH))
else
ifeq ($(CONFIG_CHIP_NAME), ap1508)
EXTRACT_SYS_IN_PATH = $(foreach tmp, $(EXTRACT_SYS_IN_SRC), $(shell find $(TOP_PATH) -name $(tmp) | grep -v "sc6138"))
$(warning $(EXTRACT_SYS_IN_PATH))
endif
endif

#$(warning $(EXTRACT_SYS_IN_OBJ))
#tmp_lib = $(foreach tmp_obj, $(EXTRACT_SYS_IN_OBJ), $(shell grep -nr $(tmp_obj) $(TOP_PATH) | head -1 | awk -F "/" '{print $NF}' | awk -F " " '{print $1}'))
#$(warning $(tmp_lib))

TOPDIR = $(KERNEL_PATH)
APPDIR = $(CLOUD_PATH)
USER_CLOUD_PATH = $(CUR_PATH)/cloudcard
USER_EXAMPLES_PATH = $(USER_CLOUD_PATH)/examples
EXCLUDE_FILE = 
EXAMPLE_PATH = $(CLOUD_PATH)/examples
#KERNEL_INC_PATH = $(TOPDIR)/../cloudcard
$(warning $(TOPDIR) $(APPDIR))

ifeq ($(CONFIG_MHD),y)
WIFI_LIB_NAME = mhd
endif
ifeq ($(CONFIG_SSV),y)
WIFI_LIB_NAME = _ssv_wifi
endif

ifeq ($(CONFIG_UI),y)
UI_PATH = $(CLOUD_PATH)/system/sl_ui
LCD_PATH = $(CLOUD_PATH)/system/sl_lcd
USER_UI_PATH = $(USER_SRC_PATH)/sl_ui
USER_LCD_PATH = $(USER_SRC_PATH)/sl_lcd
USER_UI_HEAD = $(shell cat $(UI_PATH)/Makefile | grep ^CFLAGS | awk -F "-I" '{print $$NF}' | \
		sed -s 's\#$$(APPDIR)\#'$(APPDIR)'\#' | sed -s 's\#$$(TOPDIR)\#'$(TOPDIR)'\#' | sed -s 's\#$$(CONFIG_CHIP_NAME)\#'$(CONFIG_CHIP_NAME)'\#' )
$(warning $(USER_UI_HEAD))
USER_LCD_HEAD = $(shell cat $(LCD_PATH)/Makefile | grep ^CFLAGS | awk -F "-I" '{print $$NF}' | \
		sed -s 's\#$$(APPDIR)\#'$(APPDIR)'\#' | sed -s 's\#$$(TOPDIR)\#'$(TOPDIR)'\#' | sed -s 's\#$$(CONFIG_CHIP_NAME)\#'$(CONFIG_CHIP_NAME)'\#' )
$(warning $(USER_LCD_HEAD))
CFLAGS += -I $(USER_UI_PATH)
CFLAGS += -I $(USER_LCD_PATH)

UI_PATH_SRCS = $(wildcard $(UI_PATH)/*.c)
USER_UI_ORI_OBJS = $(patsubst %.c, %.o, $(UI_PATH_SRCS))

LCD_PATH_SRCS = $(wildcard $(LCD_PATH)/*.c)
USER_LCD_ORI_OBJS = $(patsubst %.c, %.o, $(LCD_PATH_SRCS))
endif

#ifeq ($(CONFIG_SYSTEM_AIRPLAY),y)
#AIRPLAY_PATH = $(KERNEL_PATH)/../cloudcard/system/airplay
#endif
#ifeq ($(CONFIG_LOCALLIST),y)
#PLAYLIST_PATH = $(KERNEL_PATH)/../cloudcard/system/local_playlist
#endif
ifeq ($(CONFIG_SYSTEM_NXPLAYER),y)
NXPLAYER_PATH = $(KERNEL_PATH)/../cloudcard/system/nxplayer
endif

ifeq ($(PRODUCT_NAME),)
else
PRODUCT_PATH = $(KERNEL_PATH)/../cloudcard/system/$(PRODUCT_NAME)
PRODUCT_USER_PATH = $(USER_SRC_PATH)/$(PRODUCT_NAME)
ifeq ($(CONFIG_SYSTEM_MXK_NO_HDMI),y)
PRODUCT_OBJECT += mxk_vfd.o mxk_shuttle.o mxk_handle.o mxk_fm.o mxk_input.o
else
PRODUCT_OBJECT += mxk_tm1628.o mxk_hdmi.o mxk_handle_hdmi.o mxk_input_hdmi.o
endif
PRODUCT_ABS_SRC = $(patsubst %.o, $(PRODUCT_PATH)/%.c, $(PRODUCT_OBJECT))
PRODUCT_ABS_OBJ = $(patsubst %.o, $(PRODUCT_PATH)/%.o, $(PRODUCT_OBJECT))
PRODUCT_OUT_OBJ = $(patsubst %.o, $(PRODUCT_USER_PATH)/%.o, $(PRODUCT_OBJECT))
endif

IDKERNELDIR = fake
IDJSDIR     = fake
ifeq ($(CONFIG_UKERNEL_TYPE), banana)
IDMVMDIR    = fake
IDIVTDIR    = fake
IDTFSDIR    = fake
ifeq ($(CONFIG_DUEROS), y)
YOCLIBDUEROSDIR = fake
endif
ifeq ($(CONFIG_SOFTDECODE), y)
YOCLIBMADDIR = fake
YOCLIBAUDIOMODULESDIR = fake
endif
endif

ifeq ($(CONFIG_SE_GEMALTO_MTF008), y)
IDTFSHALDIR = fake
endif

ifeq ($(CONFIG_SE_SYNO_AS300), y)
IDTFSHALDIR = fake
endif

ifeq ($(CONFIG_SE_HED_CIU9872B), y)
IDTFSHALDIR = fake
endif

YOCLIBIUVDIR   = fake
YOCLIBINETUTILSDIR   = fake
YOCLIBOPUSDIR  = fake
YOCBUILDDIR = fake
#YOCLIBCRYPTO_MBEDTLS = fake
YOCLIBCUNIT = fake
YOCLIBYTEST = fake
CLOUDCARDDIR = fake

#BOARD_PATH = $(KERNEL_PATH)/hardware/id.bsp/sl_common/src
#KERNEL_OBJ = $(CUR_OBJ)/up_vectors.o $(CUR_OBJ)/crt0.o $(CUR_OBJ)/factoryset.o
#ifeq ($(CONFIG_ARCH_BACKTRACE),y)
#KERNEL_OBJ += $(CUR_OBJ)/.tmp_allsymbols.o
#endif

ifeq ($(CONFIG_ARCH_FAMILY), cskyv1)
TOOLCHAIN_PATH = csky-elf-
CC_PARAM += -mcpu=ck610e 
CFLAGS += -I $(USER_INC_PATH)/arch/cskyv1/
KERNEL_CC_PARAM += -mcpu=ck610e 
#BOARD_PATH = $(KERNEL_PATH)/hardware/id.bsp/configs/sc6138/common/src
LD_PATH = $(KERNEL_PATH)/hardware/id.bsp/configs/sc6138/common/scripts/ld.script
BUILD_TOOL_PATH = $(BUILD_TO_PATH)/nxap_tools
endif
ifeq ($(CONFIG_ARCH_FAMILY), cskyv2-l)
TOOLCHAIN_PATH = csky-abiv2-elf-
CC_PARAM += -mcpu=ck803sf
CFLAGS += -I $(USER_INC_PATH)/arch/cskyv2-l/
KERNEL_CC_PARAM += -mcpu=ck803sf
#BOARD_PATH = $(KERNEL_PATH)/hardware/id.bsp/configs/ap1508/common/src
LD_PATH = $(KERNEL_PATH)/hardware/id.bsp/configs/ap1508/common/scripts/ld.script
BUILD_TOOL_PATH = $(BUILD_TO_PATH)/nxap_tools
#KERNEL_OBJ += $(CUR_OBJ)/entry.o
endif

#include file 
CFLAGS += -I $(USER_INC_PATH)/apps
CFLAGS += -I $(USER_INC_PATH)/arch/board/
CFLAGS += -I $(USER_INC_PATH)/arch/chip/
CFLAGS += -I $(USER_INC_PATH)/arch/chip/$(CONFIG_CHIP_NAME)
#ifeq ($(CONFIG_UI),y)
#CC_PARAM += -I $(USER_UI_PATH)
#endif
CFLAGS += -I $(EXTERN_INCLUDE_PATH)
CFLAGS += -I. -isystem $(USER_INC_PATH)

#ARCHCXXFLAGS = -fno-builtin -fno-exceptions -fno-rtti -DCONFIG_CKCPU_MMU -mcpu=ck610e -mdsp
#ARCHWARNINGSXX = -Wall -Wshadow -Wundef
#ARCHOPTIMIZATION = -Os -ffunction-sections -fdata-sections -g -fno-strict-aliasing -fno-strength-reduce
#CXXFLAGS += $(ARCHCXXFLAGS) $(ARCHWARNINGSXX) $(ARCHOPTIMIZATION)
#CXXFLAGS += -I. -isystem $(USER_INC_PATH)

KERNEL_CC_PARAM += -nostartfiles -nodefaultlibs -g
KERNEL_CC_PARAM += -Wl,--gc-sections -Wl,--start-group -Wl,-whole-archive

ifeq ($(CONFIG_BUILD_PROTECTED),y)
ifeq ($(KERNEL_PATH)/ProtectedLibs.mk, $(wildcard $(KERNEL_PATH)/ProtectedLibs.mk))
include $(KERNEL_PATH)/ProtectedLibs.mk
else 
ifeq ($(CUR_PATH)/ProtectedLibs.mk, $(wildcard $(CUR_PATH)/ProtectedLibs.mk))
include $(CUR_PATH)/ProtectedLibs.mk
endif
endif
else
ifeq ($(CONFIG_BUILD_KERNEL),y)
ifeq ($(KERNEL_PATH)/KernelLibs.mk, $(wildcard $(KERNEL_PATH)/KernelLibs.mk))
include $(KERNEL_PATH)/KernelLibs.mk
else 
ifeq ($(CUR_PATH)/KernelLibs.mk, $(wildcard $(CUR_PATH)/KernelLibs.mk))
include $(CUR_PATH)/KernelLibs.mk
endif
endif
else
ifeq ($(KERNEL_PATH)/FlatLibs.mk, $(wildcard $(KERNEL_PATH)/FlatLibs.mk))
include $(KERNEL_PATH)/FlatLibs.mk
else 
ifeq ($(CUR_PATH)/FlatLibs.mk, $(wildcard $(CUR_PATH)/FlatLibs.mk))
include $(CUR_PATH)/FlatLibs.mk
endif
endif
endif
endif

LIB_KERNEL_MISC_LINK_NAME =  kernel_misc
LD_LIB_PARAM += $(patsubst lib%, -l%, $(NUTTXLIBS))
#LD_LIB_PARAM += -l$(LIB_APP_LINK_NAME)
LD_LIB_PARAM += -l$(LIB_KERNEL_MISC_LINK_NAME)
ifneq ($(EXAMPLES_OBJS), )
LD_LIB_PARAM += -lexamples
endif
LD_LIB_PARAM += -lboard  -lgcc	#need to FIXME later!!!

ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
USER_UI_ROMFS_PATH = $(USER_UI_PATH)
UI_ROMFS_DIR = $(USER_UI_ROMFS_PATH)/romfs
UI_ROMFS_IMG = $(USER_UI_ROMFS_PATH)/romfs.img
UI_ROMFS_HDR = $(USER_UI_ROMFS_PATH)/romfs.h
UI_ROMFS_TMP = $(USER_UI_ROMFS_PATH)/.tmp
endif

.PHONY : all
all :
ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
	# gen romfs.h
	$(MAKE) $(UI_ROMFS_HDR)
endif
	#fourth compile sl_ui in current src/sl_ui
	$(MAKE) other
	$(AR) rcs  $(CUR_LIB)/$(LIB_APP_NAME) $(EXAMPLES_OBJS)
	$(AR) rcs  $(CUR_LIB)/$(LIB_APP_NAME) $(EXAMPLES_CXXOBJS)
ifeq ($(CONFIG_UI),y)
	$(AR) rcs  $(CUR_LIB)/$(LIB_APP_NAME) $(USER_UI_OBJS)
	$(AR) rcs  $(CUR_LIB)/$(LIB_APP_NAME) $(USER_LCD_OBJS)
	$(CP) $(USER_UI_PATH)/tone_data.bin $(PRODUCTOUT_TO_PATH)
endif

ifeq ($(PRODUCT_NAME),)
else
ifeq ($(CONFIG_SYSTEM_MXK_NO_HDMI),y)
	$(AR) rcs  $(CUR_LIB)/$(LIB_APP_NAME) $(PRODUCT_OUT_OBJ)
else
	$(AR) rcs  $(CUR_LIB)/$(LIB_APP_NAME) $(PRODUCT_OUT_OBJ)
endif
endif

ifeq ($(EXTRACT_SYS_IN_PATH), )
else
	tmp_cnt=`cat $(OBJ_COUNT)`; \
	for i in $${tmp_cnt}; \
	do \
	echo "hhh $$i $i"; \
	tmp_lib=`awk -v line=$$i 'NR==line' $(LIB_RELATION)`; \
	tmp_obj=`awk -v line=$$i 'NR==line' $(OBJ_RELATION)`; \
	echo "xxxxx $${tmp_lib} $${tmp_obj}"; \
	$(AR) rcs  $(CUR_LIB)/$${tmp_lib} $(EXTRACT_SYS_OUT_PATH)/$${tmp_obj}; \
	done
endif

	#fifth compile zhuque use all revelant lib
	$(CC) $(KERNEL_CC_PARAM) -Wl,-T ld.script -L $(CUR_LIB) -o $(ELF_NAME) $(KERNEL_OBJ) $(LD_LIB_PARAM) -Wl,-no-whole-archive -Wl,--end-group
	$(CP) $(CUR_PATH)/dsp_firmware.bin $(PRODUCTOUT_TO_PATH)
	ls $(CUR_PATH)/$(WIFI_BIN_NAME); \
	if [ $$? = 0 ];then \
	$(CP) $(CUR_PATH)/$(WIFI_BIN_NAME) $(PRODUCTOUT_TO_PATH);\
	fi
	$(CP) $(ELF_NAME) $(PRODUCTOUT_TO_PATH)
	#make zhuqe ok!!!"

ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
.PHONY : $(UI_ROMFS_HDR)
# Create the romfs.img file from the populated romfs directory

populate: $(UI_ROMFS_DIR) $(UI_ROMFS_DIR)/001.mp3  $(UI_ROMFS_DIR)/002.mp3 $(UI_ROMFS_DIR)/003.mp3 $(UI_ROMFS_DIR)/004.mp3 $(UI_ROMFS_DIR)/005.mp3

$(UI_ROMFS_IMG): populate
	@genromfs -f $@ -d $(UI_ROMFS_DIR) -V "FLASH_MUSIC_TEST"

$(UI_ROMFS_HDR) : $(UI_ROMFS_IMG)
	@(xxd -i $(UI_ROMFS_IMG)| sed -e "s/^unsigned/static const unsigned/g" >$@)
	@(sed "s/char .*romfs_img/char romfs_img/" $@ > $(UI_ROMFS_TMP))
	@(sed "s/int .*romfs_img_len/int romfs_img_len/" $(UI_ROMFS_TMP) > $@)
	#@(xxd -i $(UI_ROMFS_IMG)| sed -e "s/^unsigned/static const unsigned/g" >$@ |sed -e "s/char .*romfs_img/romfs_img/g" >$@ |sed -e "s/char .*romfs_len/romfs_len/g" >$@)
	#@(sed -e "s/char .*romfs_img/romfs_img/g" >$@)
	#@(sed -e "s/char .*romfs_len/romfs_len/g" >$@)
endif

.PHONY : other
other: $(USER_OBJS) $(USER_CLOUD_PATH)/libexamples.a
$(USER_OBJS): %.o: %.c
	$(CC) $(CC_PARAM) $(CFLAGS) -o $@ -c $<
$(USER_CLOUD_PATH)/libexamples.a:
	$(MAKE) all -C $(USER_CLOUD_PATH) TOPDIR="$(CUR_PATH)/kernel" KERNEL=n
	ls $(USER_CLOUD_PATH)/libapps.a; \
	if [ $$? = 0 ];then \
	mv $(USER_CLOUD_PATH)/libapps.a $(CUR_LIB)/libexamples.a; \
	fi

.PHONY : clean
clean :
	for tmp in $(USER_OBJS); \
	do \
	$(RM) $${tmp};\
	done

	for tmp in $(EXAMPLES_OBJS); \
	do \
	tmp_1=`echo $${tmp} | awk -F "/" '{print $$NF}'`; \
	$(AR) -d $(CUR_LIB)/$(LIB_APP_NAME) $${tmp_1}; \
	done

	for tmp in $(EXAMPLES_CXXOBJS); \
	do \
	tmp_1=`echo $${tmp} | awk -F "/" '{print $$NF}'`; \
	$(AR) -d $(CUR_LIB)/$(LIB_APP_NAME) $${tmp_1}; \
	done

ifeq ($(CONFIG_UI),y)
	for tmp in $(USER_UI_OBJS); \
	do \
	tmp_1=`echo $${tmp} | awk -F "/" '{print $$NF}'`; \
	$(AR) -d $(CUR_LIB)/$(LIB_APP_NAME) $${tmp_1}; \
	done

	for tmp in $(USER_LCD_OBJS); \
	do \
	tmp_1=`echo $${tmp} | awk -F "/" '{print $$NF}'`; \
	$(AR) -d $(CUR_LIB)/$(LIB_APP_NAME) $${tmp_1}; \
	done
endif

ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
	$(RM)	$(UI_ROMFS_IMG)
	$(RM)	$(UI_ROMFS_HDR)
	$(RM)	$(UI_ROMFS_TMP)
endif

ifeq ($(PRODUCT_NAME),)
else
ifeq ($(CONFIG_SYSTEM_MXK_NO_HDMI),y)
	$(AR) -d  $(CUR_LIB)/$(LIB_APP_NAME) $(PRODUCT_OBJECT)
else
	$(AR) -d  $(CUR_LIB)/$(LIB_APP_NAME) $(PRODUCT_OBJECT)
endif
endif

ifeq ($(EXTRACT_SYS_IN_PATH), )
else
	tmp_cnt=`cat $(OBJ_COUNT)`; \
	for i in $${tmp_cnt}; \
	do \
	echo "hhh $$i $i"; \
	tmp_lib=`awk -v line=$$i 'NR==line' $(LIB_RELATION)`; \
	tmp_obj=`awk -v line=$$i 'NR==line' $(OBJ_RELATION)`; \
	echo "xxxxx $${tmp_lib} $${tmp_obj}"; \
	$(AR) -d $(CUR_LIB)/$${tmp_lib} $${tmp_obj}; \
	$(RM) $(EXTRACT_SYS_OUT_PATH)/$${tmp_obj}; \
	done
endif

	$(RM) out/tools/
	$(RM) out/target/product/$(BUILD_PRODUCT)/lib
	$(RM) out/target/product/$(BUILD_PRODUCT)/obj
	$(RM) out/target/product/$(BUILD_PRODUCT)/*.asm
	$(RM) out/target/product/$(BUILD_PRODUCT)/*.hex
	$(RM) out/target/product/$(BUILD_PRODUCT)/zhuque.bin
	$(RM) out/target/product/$(BUILD_PRODUCT)/bootload.bin
	$(RM) out/target/product/$(BUILD_PRODUCT)/dsp_firmware.bin
	$(RM) out/target/product/$(BUILD_PRODUCT)/$(WIFI_BIN_NAME)

	$(RM) $(ELF_NAME)
	$(RM) $(CUR_PATH)/release-images
	$(RM) $(CUR_PATH)/imgout
	$(RM) $(CUR_LIB)/libexamples.a
	$(MAKE) clean -C $(USER_CLOUD_PATH) TOPDIR="$(CUR_PATH)/kernel" KERNEL=n

.PHONY : build
build :
	#first mkdir
	$(MKDIR) $(CUR_LIB)
#$(MKDIR) $(CUR_OBJ)
	$(MKDIR) $(USER_INC_PATH)
	$(MKDIR) $(EXTERN_INCLUDE_PATH)
	$(MKDIR) $(EXTRACT_SYS_OUT_PATH)
ifeq ($(CONFIG_UI),y)
	$(MKDIR) $(USER_UI_PATH)
	$(MKDIR) $(USER_LCD_PATH)
endif
	$(MKDIR) $(USER_CLOUD_PATH)
	$(MKDIR) $(USER_EXAMPLES_PATH)

ifeq ($(PRODUCT_NAME),)
else
	$(MKDIR) $(PRODUCT_USER_PATH)
endif

	$(MKDIR) $(BUILD_TO_PATH)
	$(MKDIR) $(CUR_PATH)/kernel
	#build relation ship between lib & object
	echo $(TOP_PATH)
	echo $(EXTRACT_SYS_IN_OBJ)

ifeq ($(EXTRACT_SYS_IN_PATH), )
else
	#echo $(EXTRACT_SYS_IN_OBJ) >> $(OBJ_LIB_RELATION)
	i=1;\
	for tmp_obj in $(EXTRACT_SYS_IN_OBJ);\
	do \
	(grep -nr $${tmp_obj} $(PRODUCTOUT_FROM_PATH) | head -1 | awk -F "/" '{print $$NF}' | awk -F " " '{print $$1}') >> $(LIB_RELATION); \
	echo $${tmp_obj} >> $(OBJ_RELATION); \
	echo $${i} >> $(OBJ_COUNT); \
	i=$$(( $$i + 1)); \
	done
endif

	#wc -l $(OBJ_LIB_RELATION) | awk -F " " '{print $$1}' >> $(OBJ_COUNT)

	#second cp object from zhuque
ifeq ($(CONFIG_UI),y)
	#cat $(UI_PATH)/Makefile | grep ^CFLAGS | awk -F "-I" '{print $$NF}';
	for tmp in $(USER_UI_HEAD); \
	do \
	echo $${tmp} | grep "nxplayer"; \
	if [ $$? = 0 ];then \
	$(CP) $${tmp}/player_cmd.h $(EXTERN_INCLUDE_PATH); \
	else \
	ls $${tmp}/*.h; \
	if [ $$? = 0 ];then \
	$(CP) $${tmp}/*.h $(EXTERN_INCLUDE_PATH); \
	fi \
	fi \
	done
	$(CP) $(UI_PATH)/* $(USER_UI_PATH)

	for tmp in $(USER_LCD_HEAD); \
	do \
	ls $${tmp}/*.h; \
	if [ $$? = 0 ];then \
	$(CP) $${tmp}/*.h $(EXTERN_INCLUDE_PATH); \
	fi \
	done
	
	tmp=`find $(LCD_PATH) -name *.h`; \
	for tmp_1 in $${tmp}; \
	do \
	tmp_2=`echo $${tmp_1} | awk -F "/" '{print $$NF}'`; \
	$(RM) $(EXTERN_INCLUDE_PATH)/$${tmp_2}; \
	done

	tmp=`find $(UI_PATH) -name *.h `; \
	for tmp_1 in $${tmp}; \
	do \
	tmp_2=`echo $${tmp_1} | awk -F "/" '{print $$NF}'`; \
	$(RM) $(EXTERN_INCLUDE_PATH)/$${tmp_2}; \
	done

	$(CP) $(LCD_PATH)/* $(USER_LCD_PATH)
	$(CP) $(LCD_PATH)/romfs $(USER_LCD_PATH)
endif

ifeq ($(CONFIG_SYSTEM_UI_ROMFS),y)
	$(CP) $(UI_PATH)/romfs $(USER_UI_PATH)
endif


ifeq ($(PRODUCT_NAME),)
else
	$(CP) $(PRODUCT_ABS_SRC) $(PRODUCT_USER_PATH)
	$(CP) $(PRODUCT_PATH)/mxk_common_def.h $(PRODUCT_USER_PATH)
	$(CP) $(PRODUCT_PATH)/mxk_type.h $(PRODUCT_USER_PATH)
ifeq ($(CONFIG_SYSTEM_MXK_NO_HDMI),y)
	$(CP) $(PRODUCT_PATH)/mxk_def.h $(PRODUCT_USER_PATH)
	$(CP) $(PRODUCT_PATH)/mxk_fm.h $(PRODUCT_USER_PATH)
	$(CP) $(PRODUCT_PATH)/VFD.h $(PRODUCT_USER_PATH)
else
	$(CP) $(PRODUCT_PATH)/mxk_def_hdmi.h $(PRODUCT_USER_PATH)
	$(CP) $(PRODUCT_PATH)/TM1628.h $(PRODUCT_USER_PATH)
	$(CP) $(PRODUCT_PATH)/HDMI.h $(PRODUCT_USER_PATH)
endif
endif

	$(CP) $(KERNEL_INC_PATH)/* $(USER_INC_PATH)
#remove some not open headers
	$(RM) include/arch/chip/sc6138_gmac.h
	$(RM) include/arch/chip/sc6138_spi_ctrl.h
	$(RM) include/arch/chip/sc6138_i2c.h
	$(RM) include/arch/chip/sc6138_rtc.h
	$(RM) include/arch/chip/sc6138_eth.h
	$(RM) include/arch/chip/sc6138_pm.h
	$(RM) include/arch/chip/ltdc.h
	$(RM) include/arch/chip/dma2d.h
	$(RM) include/arch/chip/key_trans.h
	$(RM) include/arch/chip/sc6138_power.h
	$(RM) include/arch/chip/silan_powm.h
	$(RM) include/arch/chip/silan_pwm.h
	$(RM) include/arch/chip/sc6138_pwm.h
	$(RM) include/arch/chip/silan_dmac.h
	$(RM) include/arch/chip/sc6138_spise.h
	$(RM) include/arch/chip/silan_uart.h
	$(RM) include/arch/chip/silan_otghs_reg.h
	$(RM) include/arch/chip/silan_usbhost.h
	$(RM) include/arch/chip/sc6138_usb.h
	$(RM) include/arch/chip/iso7816_uart.h
	$(RM) include/arch/chip/iso7816_gpio.h
	$(RM) include/arch/chip/dma2d.h

	$(CP) $(TOP_PATH)/build/nxap_tools $(BUILD_TO_PATH)
	$(CP) $(TOP_PATH)/build/$(UPDATE_TOOL) $(CUR_PATH)
	$(RM) $(CUR_PATH)/$(UPDATE_TOOL)/in/*
	$(RM) $(CUR_PATH)/$(UPDATE_TOOL)/out/*

#ifeq ($(TOP_PATH)/$(HW_BSP_BOARD_FROM_PATH)/.gdbinit, $(wildcard $(TOP_PATH)/$(HW_BSP_BOARD_FROM_PATH)/.gdbinit))
#	$(CP) $(TOP_PATH)/$(HW_BSP_BOARD_FROM_PATH)/.gdbinit $(CUR_PATH)
#else
	$(CP) $(KERNEL_PATH)/.gdbinit $(CUR_PATH)
#endif
	$(CP) $(TOP_PATH)/out $(CUR_PATH)
	$(RM) out/tools/
	$(RM) out/target/product/$(BUILD_PRODUCT)/lib
	$(RM) out/target/product/$(BUILD_PRODUCT)/obj
	$(RM) out/target/product/$(BUILD_PRODUCT)/*.asm
	$(RM) out/target/product/$(BUILD_PRODUCT)/*.hex
	$(RM) out/target/product/$(BUILD_PRODUCT)/zhuque.bin
	$(RM) out/target/product/$(BUILD_PRODUCT)/bootload.bin
	$(RM) out/target/product/$(BUILD_PRODUCT)/dsp_firmware.bin
	$(RM) out/target/product/$(BUILD_PRODUCT)/$(WIFI_BIN_NAME)

ifeq ($(CONFIG_SYSTEM_NXPLAYER),y)
	$(CP) $(NXPLAYER_PATH)/player_cmd.h $(USER_INC_PATH)
endif

	$(CP) $(BSP_INC_PATH)/zhuque_bsp_gpio.h $(USER_INC_PATH)
	$(CP) $(BSP_INC_PATH)/zhuque_bsp_pinmux.h $(USER_INC_PATH)
	$(CP) $(BSP_INC_PATH)/bsp_errno.h $(USER_INC_PATH)
	$(CP) $(PRODUCTOUT_FROM_PATH)/lib/* $(CUR_LIB)

	ls $(PRODUCTOUT_FROM_PATH)/dsp_firmware.bin; \
	if [ $$? = 0 ];then \
	$(CP) $(PRODUCTOUT_FROM_PATH)/dsp_firmware.bin $(CUR_PATH); \
	else \
	touch $(CUR_PATH)/dsp_firmware.bin; \
	fi
	ls $(PRODUCTOUT_FROM_PATH)/$(WIFI_BIN_NAME); \
	if [ $$? = 0 ];then \
	$(CP) $(PRODUCTOUT_FROM_PATH)/$(WIFI_BIN_NAME) $(CUR_PATH);\
	fi	

ifeq ($(CONFIG_UI),y)
	$(CP) $(PRODUCTOUT_FROM_PATH)/en16dst.fnt $(CUR_PATH)
endif
	$(CP) $(CONFIG_FROM_PATH) $(CONFIG_TO_PATH)
	$(CP) $(MAKEDEFS_FROM_PATH) $(MAKEDEFS_TO_PATH)
	$(CP) $(KERNELTOOLS_FROM_PATH) $(KERNELTOOLS_TO_PATH)
	$(CP) $(CLOUD_PATH)/tools $(USER_CLOUD_PATH)
	$(CP) $(CLOUD_PATH)/Make.defs $(USER_CLOUD_PATH)
	$(CP) $(CLOUD_PATH)/Makefile $(USER_CLOUD_PATH)
	$(CP) $(CLOUD_PATH)/Application.mk $(USER_CLOUD_PATH)
	$(CP) $(CLOUD_PATH)/Directory.mk $(USER_CLOUD_PATH)
	$(CP) $(CLOUD_PATH)/examples/Make.defs $(USER_EXAMPLES_PATH)
	$(CP) $(CLOUD_PATH)/examples/Makefile $(USER_EXAMPLES_PATH)
	$(CP) $(TOP_PATH)/$(HW_BSP_CONFIG_FROM_PATH) $(CUR_PATH)
	$(RM) $(BUILD_PRODUCT)/EVB
	$(RM) $(BUILD_PRODUCT)/DVT/defconfig_release
	$(RM) $(BUILD_PRODUCT)/DVT/defconfig_silan
	$(CP) $(LD_PATH) .
	$(CP) $(KERNEL_PATH)/FlatLibs.mk $(CUR_PATH)
	$(CP) $(KERNEL_PATH)/KernelLibs.mk $(CUR_PATH)
	$(CP) $(KERNEL_PATH)/ProtectedLibs.mk $(CUR_PATH)
	$(CP) $(KERNEL_PATH)/CoreLibs.mk $(CUR_PATH)
	for tmp_1 in $(EXTRACT_EXAMPLES_FILE); \
	do \
	tmp=`find $(EXAMPLE_PATH) -name $${tmp_1}`; \
	$(CP) $${tmp} $(USER_EXAMPLES_PATH);\
	done
	#sed -i '/Application/d' $(USER_EXAMPLES_PATH)/$${tmp_1}/Makefile;

	for tmp_1 in $(EXCLUDE_FILE); \
	do \
	$(RM) $(CUR_PATH)/examples/$${tmp_1}; \
	done

ifeq ($(EXTRACT_SYS_IN_PATH), )
else
	$(CP) $(EXTRACT_SYS_IN_PATH) $(EXTRACT_SYS_OUT_PATH)
	for tmp_1 in $(EXTRACT_SYS_IN_PATH); \
	do \
	tmp=`echo "$${tmp_1%/*}"`; \
	ls $${tmp}/*.h; \
	if [ $$? = 0 ];then \
	$(CP) $${tmp}/*.h $(EXTERN_INCLUDE_PATH); \
	fi \
	done
endif

	tmp=`find . -name *.a`; \
	for tmp_1 in $${tmp}; \
	do \
	$(STRIP) --strip-unneeded $${tmp_1}; \
	done

	#third delete .o about sl_ui in libapps.a
ifeq ($(CONFIG_UI),y)
	echo $(USER_UI_ORI_OBJS)
	echo $(USER_LCD_ORI_OBJS)
	for tmp in $(USER_UI_ORI_OBJS); \
	do \
	tmp_1=`echo $${tmp} | awk -F "/" '{print $$NF}'`; \
	$(AR) -d $(CUR_LIB)/$(LIB_APP_NAME) $${tmp_1}; \
	done

	for tmp in $(USER_LCD_ORI_OBJS); \
	do \
	tmp_1=`echo $${tmp} | awk -F "/" '{print $$NF}'`; \
	$(AR) -d $(CUR_LIB)/$(LIB_APP_NAME) $${tmp_1}; \
	done
endif

ifeq ($(PRODUCT_NAME),)
else
ifeq ($(CONFIG_SYSTEM_MXK_NO_HDMI),y)
	$(AR) -d  $(CUR_LIB)/$(LIB_APP_NAME) $(PRODUCT_OBJECT)
else
	$(AR) -d  $(CUR_LIB)/$(LIB_APP_NAME) $(PRODUCT_OBJECT)
endif
endif

ifeq ($(EXTRACT_SYS_IN_PATH), )
else
	tmp_cnt=`cat $(OBJ_COUNT)`; \
	for i in $${tmp_cnt}; \
	do \
	echo "hhh $$i $i"; \
	tmp_lib=`awk -v line=$$i 'NR==line' $(LIB_RELATION)`; \
	tmp_obj=`awk -v line=$$i 'NR==line' $(OBJ_RELATION)`; \
	echo "xxxxx $${tmp_lib} $${tmp_obj}"; \
	$(AR) -d $(CUR_LIB)/$${tmp_lib} $${tmp_obj}; \
	done
endif
	echo "CFLAGS += $(CFLAGS)" >> $(MAKEDEFS_TO_PATH)
	echo "CXXFLAGS += $(CFLAGS)" >> $(MAKEDEFS_TO_PATH)

.PHONY : build_clean
build_clean :
	#make clean
	$(RM) $(CUR_LIB)
#$(RM) $(CUR_OBJ)
	$(RM) $(CUR_PATH)/ld.script
	$(RM) $(CUR_PATH)/$(ELF_NAME)
ifeq ($(CONFIG_UI),y)
	$(RM) $(USER_UI_PATH)
	$(RM) $(USER_LCD_PATH)
	$(RM) $(CUR_PATH)/en16dst.fnt
endif
	$(RM) $(USER_CLOUD_PATH)
	$(RM) $(CUR_PATH)/kernel

ifeq ($(PRODUCT_NAME),)
else
	$(RM) $(PRODUCT_USER_PATH)
endif

	$(RM) $(USER_INC_PATH)
	$(RM) $(EXTERN_INCLUDE_PATH)
	$(RM) $(EXTRACT_SYS_OUT_PATH)
	$(RM) $(BUILD_TO_PATH)
	$(RM) $(UPDATE_TOOL)
	$(RM) $(BUILD_PRODUCT)
	$(RM) $(CUR_PATH)/dsp_firmware.bin
	$(RM) $(CUR_PATH)/$(WIFI_BIN_NAME)

	$(RM) $(CUR_PATH)/.gdbinit
	$(RM) $(CUR_PATH)/.config
	$(RM) $(CUR_PATH)/FlatLibs.mk
	$(RM) $(CUR_PATH)/KernelLibs.mk
	$(RM) $(CUR_PATH)/ProtectedLibs.mk
	$(RM) $(CUR_PATH)/CoreLibs.mk
	$(RM) $(CUR_PATH)/release-images
	#$(RM) $(USER_EXAMPLES_PATH)
	#for tmp_1 in $(EXTRACT_EXAMPLES_FILE); \
	#do \
	#tmp=`find $(USER_EXAMPLES_PATH) -name $${tmp_1}`; \
	#$(RM) $${tmp};\
	#done
	$(RM) $(CUR_PATH)/imgout
	$(RM) $(CUR_PATH)/out
	$(RM) $(CONFIG_TO_PATH)
	$(RM) $(MAKEDEFS_TO_PATH)
	$(RM) $(KERNELTOOLS_TO_PATH)
	$(RM) $(LIB_RELATION)
	$(RM) $(OBJ_RELATION)
ifeq ($(EXTRACT_SYS_IN_PATH), )
else
	$(RM) $(OBJ_COUNT)
endif

.PHONY : flash
flash :
	make all
	export PATH=$(PATH):$(BUILD_TOOL_PATH) && imgout || joint.sh
	cd release-images/;\
	../out/tools/imgmk/mkflash_ap.sh;\
	cd -
