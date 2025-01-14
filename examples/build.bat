@echo off
gcc -o demo.exe main.c -lgdi32 -luser32 -lwinmm -O3 -Wall -s -fno-strict-aliasing -fomit-frame-pointer