#!/bin/bash
############################################################################
# Makefile.modpost
#
# Copyright (C) 2015 YunOS Project. All rights reserved.
############################################################################

echo "#include <nuttx/module.h>" > $1
grep "undefined reference to" $2 -rn | awk -F "\`" '{print $2}' | awk -F "\'" '{print "extern int "$1"(void);EXPORT_SYMBOL_NOUSED("$1");"}' > /tmp/.module_build_info1
sort /tmp/.module_build_info1 | uniq >> $1
rm $2 /tmp/.module_build_info1
