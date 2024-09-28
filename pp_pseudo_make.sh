#!/bin/bash

x86_64-w64-mingw32-g++ -O2 ./$1/$2.cpp -o ./$1/build/$2.exe -I/usr/share/mingw-w64/include/ -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc -fpermissive