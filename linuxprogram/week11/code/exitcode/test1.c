#include "my.h"

int main()
{
	pid_t pid,s;
	if ((pid=fork())<0)
	{
		perror("failed to fork\n");
		return -1;
	}
	else if (pid ==0)
	{
		printf("child:pid=%d,ppid=%d\texit now\n",getpid(),getppid());
		exit(0);
	}
	else
	{
		printf("parent:pid=%d,ppid=%d\texit now\n",getpid(),getppid());
		while(1) 1;
		
		exit(0);
	}
	exit(0);
}
