#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int x=100;
int main()
{
	int y=0;
	static int w = 10;
	printf("test1:pid=%d,ppid=%d\n",getpid(),getppid());
	printf("test1:address x=%u,y=%u,w=%u\n",&x,&y,&w);
	sleep(5);
	return 0;
}
