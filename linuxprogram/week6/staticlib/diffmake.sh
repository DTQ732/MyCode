#!/bin/bash -v
gcc -c fun1.c fun2.c
ar -rc /home/gitrepo/runoob.git/MyCode/staticlib/lib/libmy.a fun1.o fun2.o 
gcc -o main main.c -L/home/gitrepo/runoob.git/MyCode/staticlib/lib -lmy
