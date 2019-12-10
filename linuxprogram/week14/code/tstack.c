#include "my.h"

int i=0;
void foo()
{
	int buff[256]={0};
	i++;
	printf("i = %d\n",i);
	foo();
}

int main()
{
	foo();
	return 0;
}
