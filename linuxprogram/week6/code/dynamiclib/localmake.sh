#!/bin/bash -v
gcc -fPIC -shared -o libmydld.so mydld.c	#build dll command
gcc -o slocaltest localtest.c -ldl -w		#compiler
########开始运行########
./slocaltest					#run
