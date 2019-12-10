#include <stdio.h>

int addr=0;

int loop(int *p)
{
	printf("loop %x\n",loop);
	printf("p    %u\n",(int*)(&p));
	

	printf("add -4 %x\n",(int*)(&p-1));
	*(int*)(&p-1) = &p-4;
	printf("add +4 %x\n",(int*)(&p+1));
	//*(int*)(&p+1) = loop;
	printf("$p = %d\n",*p);
	*p++;
	
	getchar();
	return 0; 
}

int main()
{
	int a = 1;
	int *p = &a; 
	printf("p    %u\n",(int*)(&p));
	
	loop(p);
	printf("end\n");
	return 0;
}
