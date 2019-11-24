#include "my.h"

/*
在执行fork/vfork操作后，父进程会复制所有的资源，包括文件描述符给子进程。编程验证父子进程对于相同文件操作时，是否会相互影响，即两者是会共享文件指针，还是拥有自己各自独立的指针体系。请编写两个版本（fork版和vfork版），实验结果贴图于答案区并附文字说明。源代码附件形式提交。
*/

static void __attribute__ ((constructor)) before_main(){
	printf("--------constructor--------\n");
}

static void __attribute__ ((destructor)) after_main(){
        printf("--------destructor--------\n");
}

int main(int argc,char*argv[])
{
	int pid1,pid2;
	FILE*fp;
	
	if((fp=fopen("test1.dat","w"))==NULL)
	{
		perror("failed to fopen!\n");
		return -1;	
	}
	
	printf("before fork\n");
	
	pid1=fork();
	
	if (pid1 >0)
		pid2=fork();
	
	
	
	
	if (pid1==0 || pid2 ==0)
	{
		char buf[128]={0};
		sprintf(buf,"0123456789 child:pid=%d,ppid=%d\n",getpid(),getppid());
		
		if (fputs(buf,fp)==EOF)
		{
			perror("child:failed to fputs\n");
		}
		fflush(fp);
		sleep(2);
		if (fputs(buf,fp)==EOF)
		{
			perror("child:failed to fputs\n");
		}
		fflush(fp);
		sleep(2);
		if (fputs(buf,fp)==EOF)
		{
			perror("child:failed to fputs\n");
		}
		fflush(fp);
		exit(0);
	}
	
	printf("parent:pid=%d,ppid=%d\n",getpid(),getppid());
	int n=0;
	while((pid1=wait(NULL))>=0 && n<=2)
	{
		n++;
	}
	system("cat test1.dat");
		
	return 0;
}
