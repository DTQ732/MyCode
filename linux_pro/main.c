#include "uhead.h"
int main()
{
	int a[UNUMBER];
	struct arg t;
	urand(a,UNUMBER);
	show(a,UNUMBER);
	t=operater(a,UNUMBER);
	printf("sun-%d ,ave%f\n",t.sum,t.ave);
	return 0;
}
