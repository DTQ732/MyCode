#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int ret;
	printf("caller:pid=%d,ppid=%d\n",getpid(),getppid());
	ret=system("/home/gitrepo/runoob.git/MyCode/linuxprogram/week9/code/caller/t 123 456");
	printf("after calling\n");
	return 0;
}
