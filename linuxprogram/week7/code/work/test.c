#include "func.h"



void meun()
{
	int choic=-1;
	char name[260]={0};
	char buf[1024]={0};
	int fd,fd1,fd2;
	system("reset");
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
				creatfile_1(&fd,name);
			break;
			case 2:
				writefile_1(fd,buf);
			break;
			case 3:
				readfile(fd,buf);
			break;
			case 4:
				modifyauthority(fd,buf);
			break;
			case 5:
				checkauthority(fd,buf);
				break;
		}
		choic=0;
	}
	close(fd);
	sprintf(buf,"rm %s",name);
	system(buf);
}

int main()
{
	meun();
}
