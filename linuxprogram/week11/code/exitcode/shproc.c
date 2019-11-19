#include <time.h>
#include "my.h"
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/param.h>
#include <unistd.h>
void init_daemon(void)
{
	pid_t child1,child2;
	int i;
	child1 =fork();
	if(child1>0) exit(0);	//
	else if (child1<0)
	{
		perror("fail");
		exit(1);
	}
	setsid();
	chdir("/tmp");
	umask(0);
	for(i=0;i<NOFILE;++i)
		close(i);
	return;
}

int main()
{
	FILE*fp;
	time_t t;
	init_daemon();
	while(1)
	{
		sleep(10);
		if ((fp=fopen("6-8.log","a"))>=0)
		{
			t=time(0);
			fprintf(fp,"守护进程正在运行 time: %s",asctime(localtime(&t)));
			fclose(fp);
		}
	}
}
