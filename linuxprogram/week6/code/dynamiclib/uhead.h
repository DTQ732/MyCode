#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNUMBER 10000

struct arg{
	float ave;
	int sum;
};

void show(int *,int );
void urand(int *,int );

int compar(const void*a,const void*b);
void Syssort(int *a,int n,int(*compar)(const void *,const void *));
void Mysort(int *a,int n,int(*compar)(const void *,const void *));
