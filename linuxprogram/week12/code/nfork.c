#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

int main()
{
	srand(time(0));
	pid_t r;
	int s1,s2,s3,r1,r2,r3;
	int forkn=rand()%8;
	printf("\nparent proc pid = %d ,ppid = %d\n",getpid(),getppid());
	printf("fork num = %d\n begin fork\n",forkn);
	int i=0;
	for (;i<forkn;i++)
	{
		r = fork();
		if (r==0)
			break;
		else if (r < 0)
			exit(-1);
	}

	if (r == 0)
		printf("child proc %d pid = %d ,ppid = %d\n",i,getpid(),getppid());
	if (r == 0 && i == 0)
	{
		//
	}
	
	sleep(forkn);
	return 0;
}
