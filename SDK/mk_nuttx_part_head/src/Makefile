include config
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %, $(SRC))
UPDATE_IN=../in/$(UPDATE_BIN_IN)
UPDATE_OUT=../out/update.binary
SYS_VERSION=$(shell grep -ar -m1 -z "zhuque_20" ${UPDATE_IN})
ARCH_VERSION_1=$(shell grep -ar -m1 -z "csky-v1" ${UPDATE_IN})
ARCH_VERSION_2=$(shell grep -ar -m1 -z "csky-v2" ${UPDATE_IN})
PRODUCT_VERSION=$(shell grep -ar -m1 -z "product_version_" ${UPDATE_IN})
$(warning "arch version 1" $(ARCH_VERSION_1))
$(warning "arch version 2" $(ARCH_VERSION_2))
$(warning "product version" $(PRODUCT_VERSION))

%.o:%.c
	$(CC) -c $@
%:%.o
	$(CC) -o $@

all:$(OBJ) $(UPDATE_OUT)

$(UPDATE_OUT):
	./add_part_head_info $(UPDATE_IN) $(UPDATE_OUT) $(UPDATE_START_ADDR) $(UPDATE_LEN) $(SYS_VERSION) $(ARCH_VERSION_1) $(ARCH_VERSION_2) $(PRODUCT_VERSION)

clean:
	rm -rf $(OBJ) $(UPDATE_OUT)
