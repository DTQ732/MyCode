#include "my.h"

void sighandler(int signo);

int main()
{
	int fd[2];
	if(signal(SIGPIPE,sighandler)==SIG_ERR)
	{
		fprintf(stderr,"signal error (%s)\n",strerror(errno));
		exit(-1);
	}
	if(pipe(fd) == -1)
	{
		fprintf(stderr,"create pipe error (%s)\n",strerror(errno));
		exit(-2);
	}
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		fprintf(stderr,"fork error (%s)\n",strerror(errno));
		exit(-3);
	}
	else if (pid==0)
	{
		fprintf(stdout,"[child] i will close the last read ebd of pipe.pid=%d ppid=%d\n",getpid(),getppid());
		sleep(2);
		close(fd[0]);
		exit(0);
	}
	else
	{
		sleep(3);
		//close(fd[0]);
		int ret;
		ret = write(fd[1],"hello",5);
		if(ret==-1)
		{
			fprintf(stderr,"parent write error (%s)\n",strerror(errno));
		}
		else fprintf(stdout,"parent write success\n");
		return 0;
	}
}
void sighandler(int signo)
{
	fprintf(stderr,"parent catch a error (%d)\n",signo);
}
