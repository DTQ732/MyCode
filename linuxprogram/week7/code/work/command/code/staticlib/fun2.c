#include "uhead.h"

struct arg operater(int *a,int n)
{
	struct arg k;
	int i;
	k.sum=0;k.ave=0.0;
	for(i=0;i<n;i++)
	{
		k.sum=k.sum+a[i];
	}
	k.ave=((float)k.sum)/n;
	return k;
}

int compar(const void*a,const void*b)
{
	int ia=*(int*)a,ib=*(int*)b;
	if(ia>ib) return 1;
	if(ia==ib) return 0;
	if(ia<ib) return -1;
}
void Syssort(int *a,int n)
{
	qsort(a,n,sizeof(int),compar);
}
void Mysort(int *a,int n)
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
