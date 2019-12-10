#include "my.h"

//pipe long 65536
int main()
{
	pid_t r;
	int r_num;
	int s1,s2,s3,r1,r2,r3;
	int pipefd[2];
	int piped[2];
	char buf[4096];
	memset(buf,0,sizeof(buf));
	
	if (pipe(pipefd) <0)
	{
		perror("fail pipe\n");
		return -1;
	}
	if (pipe(piped) <0)
	{
		perror("fail pipe\n");
		return -1;
	}
	int i=0;

	for (;i<3;i++)
	{
		r = fork();
		
		if (r==0)
		{
			printf("             pid = %d,ppid = %d\n",getpid(),getppid());
			break;
		}
		
		else if (r < 0)
		{
			perror("In fork %dth faided,sorry!\n");
			exit(-1);
		}
	}
	
sleep(5);
	
//child proc 1
	if (r==0 && i == 0)
	{
		printf("child proc 1 pid = %d,ppid = %d\n",getpid(),getppid());
		exit(1);

	}
//child proc 2
	if (r == 0 && i == 1)
	{
		printf("child proc 2 pid = %d,ppid = %d\n",getpid(),getppid());
		exit(2);

	}
//child proc 3
	if (r == 0 && i == 2)
	{
		printf("child proc 3 pid = %d,ppid = %d\n",getpid(),getppid());
		exit(3);
	}

/*	
	close(pipefd[0]);
	int i=0;
	char * w = "a";
	for(i=0;i<65537;i++)
	{
		if(write(pipefd[1],w,1)!= -1)
		{
			printf("pipe long %d\n",i);	
			continue;
		}
		return -1;
	}
	close(pipefd[1]);
*/
	r1 = wait(&s1);
	r2 = wait(&s2);
	r3 = wait(&s3);
	return 0;
}
