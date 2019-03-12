SRC_PATH = ${shell pwd}/src

EXTRACT_SYS_IN_NAME = $(SRC_PATH)/../extract_sys_name
EXTRACT_PRODUCT_IN_NAME = $(SRC_PATH)/../extract_product_name
CUSTOM = $(shell cat $(EXTRACT_PRODUCT_IN_NAME))
$(warning $(CUSTOM))

EXTRACT_SYS_OUT_PATH_1 = $(SRC_PATH)/xxx_board
SL_UI_PATH_1 = $(SRC_PATH)/xxx_ui
SL_LCD_PATH_1 = $(SRC_PATH)/xxx_lcd

EXTRACT_SYS_OUT_PATH = $(subst xxx,$(CUSTOM),$(EXTRACT_SYS_OUT_PATH_1))
SL_UI_PATH = $(subst xxx,$(CUSTOM),$(SL_UI_PATH_1))
SL_LCD_PATH = $(subst xxx,$(CUSTOM),$(SL_LCD_PATH_1))

$(warning (EXTRACT_SYS_OUT_PATH))
$(warning $(SL_UI_PATH))
$(warning $(SL_LCD_PATH))

EXTRACT_SYS_IN_SRC = $(shell cat $(EXTRACT_SYS_IN_NAME))
EXTRACT_SYS_IN_OBJ = $(patsubst %.c, %.o, $(EXTRACT_SYS_IN_SRC))
EXTRACT_SYS_OUT_OBJ = $(addprefix $(EXTRACT_SYS_OUT_PATH)/, $(EXTRACT_SYS_IN_OBJ))
USER_OBJS += $(EXTRACT_SYS_OUT_OBJ)
$(warning $(EXTRACT_SYS_IN_SRC))
$(warning $(EXTRACT_SYS_IN_OBJ))

SL_UI_SRCS = $(wildcard $(SL_UI_PATH)/*.c)
USER_UI_OBJS += $(patsubst %.c, %.o, $(SL_UI_SRCS))
USER_OBJS += $(USER_UI_OBJS)

SL_LCD_SRCS = $(wildcard $(SL_LCD_PATH)/*.c)
USER_LCD_OBJS += $(patsubst %.c, %.o, $(SL_LCD_SRCS))
USER_OBJS += $(USER_LCD_OBJS)

EXTRACT_EXAMPLES_IN_NAME = $(SRC_PATH)/../extract_examples_name
EXTRACT_EXAMPLES_FILE = $(shell cat $(EXTRACT_EXAMPLES_IN_NAME))
#ifeq ($(PRODUCT_NAME),)
#else
#USER_OBJS += $(addprefix $(PRODUCT_USER_PATH)/, $(PRODUCT_OBJECT))
#endif
#

#USER_PATH = $(SRC_PATH)/user
#USER_SRCS = silan_user.c
#USER_OBJS += $(addprefix $(USER_PATH)/, $(patsubst %.c,%.o,   \
#						$(USER_SRCS)))
#
