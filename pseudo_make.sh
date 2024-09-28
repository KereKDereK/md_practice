#!/bin/bash

x86_64-w64-mingw32-gcc ./$1/$2.cpp -o ./$1/build/$2.exe -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc > $2_make_log.txt