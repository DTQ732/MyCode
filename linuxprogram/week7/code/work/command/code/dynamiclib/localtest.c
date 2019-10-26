#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <time.h>

#define UNUMBER 10000

int main()
{	
	int a[UNUMBER];
	int choic=0;
	time_t at=clock(),bt=clock();
	void * hd =dlopen("./libmydld.so",RTLD_LAZY);
	void (*pshow)(int *,int);
	void (*purand)(int *,int);
	void (*pSyssort)(int *,int,int(*compar)(const void *,const void *));
	void (*pMysort)(int *,int,int(*compar)(const void *,const void *));
	int (*pcompar)(const void*,const void*);

	if (!hd){
		fprintf(stderr,"%s\n",dlerror());
		exit(-1);
	}

	pshow=dlsym(hd,"show");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}

	purand=dlsym(hd,"urand");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}
	pSyssort=dlsym(hd,"Syssort");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}
	pMysort=dlsym(hd,"Mysort");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}
	pcompar=dlsym(hd,"compar");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}

	printf("show unumber?\n 1.yes 2.no");
	scanf("%d",&choic);
	purand(a,UNUMBER);
	at = clock();
	pSyssort(a,UNUMBER,pcompar);
	if(choic==1)
	pshow(a,UNUMBER);
	bt = clock();
	printf("Syssort times = %lf\n",(bt*1.0-at)/CLOCKS_PER_SEC);
	purand(a,UNUMBER);
	at = clock();
	pMysort(a,UNUMBER,pcompar);
	bt = clock();
	printf("Mysort times = %lf\n",(bt*1.0-at)/CLOCKS_PER_SEC);

	if(choic==1)
	pshow(a,UNUMBER);

	printf("Sort %d numbers\n",UNUMBER);
	return 0;
	
}
