#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	char * arg[]={"./test2","123","abc",NULL};
	printf("execvp caller:pid=%d,ppid=%d\n",getpid(),getppid());
	
	int ret = execvp("test2",arg);
	printf("after calling,ret=%d\n",ret);
	return 0;
}
