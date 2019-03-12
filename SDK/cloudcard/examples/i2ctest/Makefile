############################################################################
# apps/examples/i2ctest/makefile
# Driver for SPI-based MX25L6433F (64Mbit) flash.
#
#Copyright (C) 2015 The YunOS Open Source Project
#
#Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#
############################################################################

-include $(TOPDIR)/Make.defs

# Hello, World! built-in application info

APPNAME = i2ctest
PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 2048

# I2C Example

ASRCS =
ifeq ($(CONFIG_EXAMPLES_I2CTEST),y)
CSRCS += zlg7290.c
endif
MAINSRC = i2ctest_main.c

CONFIG_EXAMPLES_XYZ_PROGNAME ?= i2ctest$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_XYZ_PROGNAME)

include $(APPDIR)/Application.mk
