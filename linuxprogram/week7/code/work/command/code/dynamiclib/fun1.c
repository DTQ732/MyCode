#include "uhead.h"

void show(int *a,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("a[%d]=%d\t",i,a[i]);
		if(i && i%6==0) printf("\n");
	}
	printf("\n");
}

void urand(int *a,int n)
{
	int i;
	srand((int)time(0));
	
	for(i=0;i<n;i++)
	{
		a[i]=1+(int)(1000.0*rand()/(RAND_MAX+1.0));
	}
}
