#!/bin/bash
# hardware/id.bsp/configs/sc6138a-xj-1/DVT/setenv.sh
#

if [ "$_" = "$0" ] ; then
  echo "You must source this script, not run it!" 1>&2
  exit 1
fi

WD=`pwd`
if [ ! -x "setenv.sh" ]; then
  echo "This script must be executed from the top-level Yoc build directory"
  exit 1
fi

if [ -z "${PATH_ORIG}" ]; then
  export PATH_ORIG="${PATH}"
fi

export TOOLCHAIN_BIN=${WD}"/../build/toolchain_xj/bin/"
export PATH="${TOOLCHAIN_BIN}:${PATH_ORIG}"

echo "PATH : ${PATH}"


