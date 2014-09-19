#!/bin/sh

make clean
rm -f CMakeCache.txt
find . -name "CMakeFiles" -print0|xargs -0 rm -Rf

