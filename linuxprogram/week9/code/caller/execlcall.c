#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int ret;
	printf("caller:pid=%d,ppid=%d\n",getpid(),getppid());
	execl("/home/gitrepo/runoob.git/MyCode/linuxprogram/week9/code/caller/test2","123","456",NULL);
	printf("after calling\n");
	return 0;
}
