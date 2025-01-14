@echo off
gcc -o demo.exe image.c -lgdi32 -luser32 -lwinmm -O3 -Wall -s -fno-strict-aliasing -fomit-frame-pointer