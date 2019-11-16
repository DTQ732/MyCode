#include "h.h"

/*
在执行fork/vfork操作后，父进程会复制所有的资源，包括文件描述符给子进程。编程验证父子进程对于相同文件操作时，是否会相互影响，即两者是会共享文件指针，还是拥有自己各自独立的指针体系。请编写两个版本（fork版和vfork版），实验结果贴图于答案区并附文字说明。源代码附件形式提交。
*/

static void callback1(){
	printf("--------callback1---------\n");
}

static void callback2(){
        printf("--------callback2---------\n");
}

static void __attribute__ ((constructor)) before_main(){
	printf("--------constructor--------\n");
}

static void __attribute__ ((destructor)) after_main(){
        printf("--------destructor--------\n");
}

int main(int argc,char*argv[])
{
	atexit(callback1);
	atexit(callback2);
	FILE*fp;
	int fd;
	char buf1[]="child :test data from full buffer!\n";
	char buf2[]="parent:test data from full buffer!\n";
	if((fp=fopen("test1.dat","w"))==NULL)
	{
		perror("failed to fopen!\n");
		return -1;	
	}
	
	if ((fd = open("test2.dat",O_RDWR|O_TRUNC|O_CREAT,0666)) == -1)
	{
		perror("failed to fopen!\n");
		return -1;	
	}
	pid_t pid;
	pid = fork();
	
	if (pid==0)
	{
		printf("child:pid=%d,ppid=%d\n",getpid(),getppid());
		
		if (fputs(buf1,fp)==EOF)
		{
			perror("child:failed to fputs\n");
		}
		
		if (write(fd,buf1,sizeof(buf1)+1) == EOF)
		{
			perror("child:failed to fputs\n");
		}
	}
	else if (pid >0)
	{
		printf("parent:pid=%d,ppid=%d\n",getpid(),getppid());
		
		if (fputs(buf2,fp)==EOF)
		{
			perror("failed to fputs\n");
		}
		printf("printf:data from line buffer");
	
		if (write(fd,buf2,sizeof(buf2)+1) == EOF)
		{
			perror("failed to fputs\n");
		}
	}
	
	
	
}
