#!/bin/sh

rm -f CMakeCache.txt
find . -name "CMakeFiles" -print0|xargs -0 rm -Rf
export TOOLCHAIN_ROOT=/usr/bin/
cmake CMakeLists.txt -DTARGET="emulator"

