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
