EXAMPLES_PATH = ${shell pwd}/src

$(shell rm $(EXAMPLES_PATH)/examples_list.h)
$(shell rm $(EXAMPLES_PATH)/examples_proto.h)

ifeq ($(CONFIG_EXAMPLES_I2CTEST), y)
$(shell echo '{"i2ctest", i2ctest_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int i2ctest_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_I2STEST), y)
$(shell echo '{"i2stest", i2stest_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int i2stest_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_ROMFS), y)
$(shell echo '{"romfs", romfs_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int romfs_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_RTCTEST), y)
$(shell echo '{"rtctest", rtctest_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int rtctest_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_IPERF), y)
$(shell echo '{"iperf", iperf_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int iperf_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_WGET), y)
$(shell echo '{"wget", wget_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int wget_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_GPIOTEST), y)
$(shell echo '{"gpiotest", gpiotest_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int gpiotest_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_UARTTEST), y)
$(shell echo '{"uarttest", uarttest_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int uarttest_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

ifeq ($(CONFIG_EXAMPLES_FLOWPLAY), y)
$(shell echo '{"flowplay", flowplay_main},' >> $(EXAMPLES_PATH)/examples_list.h)
$(shell echo 'int flowplay_main(int argc, char *argv[]);' >> $(EXAMPLES_PATH)/examples_proto.h)
endif

EXAMPLES_REGSTER_SRC = $(shell cat $(EXAMPLES_PATH)/examples_proto.h)
ifneq ($(EXAMPLES_REGSTER_SRC), )
EXAMPLES_REGSTER_SRC = $(EXAMPLES_PATH)/examples_register.c
endif
EXAMPLES_OBJS = $(patsubst %.c, %.o, $(EXAMPLES_REGSTER_SRC))
USER_OBJS += $(EXAMPLES_OBJS)
