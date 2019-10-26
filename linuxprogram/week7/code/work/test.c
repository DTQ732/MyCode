#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

const char *infor[8]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};

void meun()
{
	int choic=-1;
	char name[260]={0};
	char buf[1024]={0};
	int fd,fd1,fd2;

	printf("****************\n");
	printf("0.退出\n");
	printf("1.创建新文件\n");
	printf("2.写文件\n");
	printf("3.读文件\n");
	printf("4.修改文件权限\n");
	printf("5.查看当前文件的权限,并修改权限\n");
	printf("****************\n");
	
	while(1)
	{
		printf("Please input your choice(0-5):");
		scanf("%d",&choic);
		switch(choic)
		{
			case 0:
			exit(-1);
			break;
			case 1:
				printf("Please input file name:");
				scanf("%s",name);
				if ((fd = creat(name,O_RDWR|S_IREAD|S_IWRITE)) < 0)
		 	   {
		            fprintf(stderr,"ERROR\n");
		 	   }
		 	        
			break;
			case 2:
				printf("Please input write types:");
				scanf("%s",buf);
				write(fd,buf,strlen(buf)+1);
			break;
			case 3:
				lseek(fd,0,SEEK_SET);
				read(fd,buf,1023);
				printf("%s\n",buf);
			break;
			case 4:{
				printf("please input file rights:");
				scanf("%s",buf);
				int r = (buf[0]-'0')*64 + (buf[1]-'0')*8+(buf[0]-'0');
				fchmod(fd,r);
				break;
				}
			case 5:{
				struct stat st;
				fstat(fd,&st);
				sprintf(buf,"%o\n",st.st_mode);
				printf("属主权限 %s",infor[buf[3]-'0']);
				printf(" 组权限  %s",infor[buf[4]-'0']);
				printf("其他权限 %s\n",infor[buf[5]-'0']);
				break;
			}
		}
	}
	close(fd);
}

int main()
{
	meun();
}
