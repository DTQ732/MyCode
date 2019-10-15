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
struct arg operater(int *,int );

int compar(const void*a,const void*b);
void Syssort(int *,int n);
void Mysort(int *,int n);
