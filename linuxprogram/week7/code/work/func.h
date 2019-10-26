#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dlfcn.h>

void creatfile_1(int * fd,char *name);
void writefile_1(int fd,char * buf);
void readfile(int fd,char *buf);
void modifyauthority(int fd,char *buf);
void showauthority(int fd,char * buf);
void checkauthority(int fd,char *buf);
