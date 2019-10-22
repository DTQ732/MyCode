#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int globa =4;
int main()
{
	pid_t pid;
	int vari = 5;
	printf("before fork\n");

	if ((pid=fork())<0){
	printf("fork error\n");	
	}else if (pid == 0)
	{
		globa++;
		vari--;
		printf("Child changed\n");
		printf("Child :globa = %d vari =%d\n",globa,vari);
	}
	else
	{
		printf("Parent did not changed\n");
                printf("Child :globa = %d vari =%d\n",globa,vari);
		exit(0);
	}

}
