#!/bin/bash -v
gcc -c func.c
ar -rc libfunc.a func.o
rm *.o
gcc -fPIC -shared -o libmeun.so meun.c
gcc -o localtest test.c -L. -lfunc -ldl -w
