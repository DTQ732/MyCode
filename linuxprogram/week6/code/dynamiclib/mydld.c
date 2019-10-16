#include "mydld.h"

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

int compar(const void*a,const void*b)
{
	int ia=*(int*)a,ib=*(int*)b;
	if(ia>ib) return 1;
	if(ia==ib) return 0;
	if(ia<ib) return -1;
}
void Syssort(int *a,int n,int(*compar)(const void *,const void *))
{
	qsort(a,n,sizeof(n),compar);
}
void Mysort(int *a,int n,int(*compar)(const void *,const void *))
{
	int i=0,j=0,temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(compar((void *)&a[j],(void *)&a[j+1])==1)
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
