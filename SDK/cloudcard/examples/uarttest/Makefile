############################################################################
# apps/examples/uarttest/Makefile
#
# Copyright (C) 2015 The YunOS Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
############################################################################

-include $(TOPDIR)/Make.defs

# Hello, World! built-in application info

APPNAME = uarttest
PRIORITY = SCHED_PRIORITY_DEFAULT
STACKSIZE = 2048

# Hello, World! Example

ASRCS =
CSRCS =
MAINSRC = uarttest_main.c

CONFIG_EXAMPLES_XYZ_PROGNAME ?= uarttest$(EXEEXT)
PROGNAME = $(CONFIG_EXAMPLES_XYZ_PROGNAME)

include $(APPDIR)/Application.mk
