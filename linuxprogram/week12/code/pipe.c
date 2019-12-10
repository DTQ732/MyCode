#include "my.h"

int main()
{
	pid_t r;
	int r_num;
	int pipefd[2];
	char buf[4096];
	memset(buf,0,sizeof(buf));
	
	if (pipe(pipefd) <0)
	{
		perror("fail pipe\n");
		return -1;
	}
	
	r = fork();
	
	if (r<0)
	{
		perror("fork failed\n");
		return -1;
	}
	
	else if (r==0)
	{
		sleep(10);
		close(pipefd[1]);
		if((r_num = read(pipefd[0],buf,100))>0)
			printf("child read %s num = %d\n",buf,r_num);
		close(pipefd[0]);
		exit(0);
	}
	else
	{
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
		return 0;
	}
	return 0;
	
}
