#!/bin/bash

x86_64-w64-mingw32-g++ -shared -o ./$1/build/$2.dll ./$1/$2.cpp -fpermissive > $2_make.log