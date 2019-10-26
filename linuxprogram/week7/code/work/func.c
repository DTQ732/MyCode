#include "func.h"

const char *infor[8]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};

void creatfile_1(int * fd,char *name)
{
	printf("Please input file name:");
	scanf("%s",name);
	if ((*fd = creat(name,O_RDWR|S_IREAD|S_IWRITE)) < 0)
	{
		fprintf(stderr,"ERROR\n");
	}
	return;
}
void writefile_1(int fd,char * buf)
{
	printf("Please input write types:");
	scanf("%s",buf);
	write(fd,buf,strlen(buf)+1);
}

void readfile(int fd,char *buf)
{
	lseek(fd,0,SEEK_SET);
	read(fd,buf,1023);
	printf("%s\n",buf);
}
void modifyauthority(int fd,char *buf)
{
	printf("please input file rights:");
	scanf("%s",buf);
	int r = (buf[0]-'0')*64 + (buf[1]-'0')*8+(buf[0]-'0');
	fchmod(fd,r);
}
void checkauthority(int fd,char *buf)
{
	struct stat st;
	fstat(fd,&st);
	sprintf(buf,"%o\n",st.st_mode);
	printf("属主权限 %s",infor[buf[3]-'0']);
	printf(" 组权限  %s",infor[buf[4]-'0']);
	printf("其他权限 %s\n",infor[buf[5]-'0']);
	modifyauthority(fd,buf);
}
