#include "uhead.h"
int main()
{
	int a[UNUMBER];
	int choic=0;
	struct arg t;
	time_t at=clock(),bt=clock();

	printf("show unumber?\n 1.yes 2.no");
	scanf("%d",&choic);
	urand(a,UNUMBER);
	if(choic==1)
	show(a,UNUMBER);
	at = clock();
	Syssort(a,UNUMBER);
	bt = clock();
	printf("Syssort times = %lf\n",(bt*1.0-at)/CLOCKS_PER_SEC);
	urand(a,UNUMBER);
	at = clock();
	Mysort(a,UNUMBER);
	bt = clock();
	printf("Mysort times = %lf\n",(bt*1.0-at)/CLOCKS_PER_SEC);

	if(choic==1)
	show(a,UNUMBER);
	//t=operater(a,UNUMBER);
	//printf("sun-%d ,ave%f\n",t.sum,t.ave);
	printf("Sort %d numbers\n",UNUMBER);
	return 0;
}
