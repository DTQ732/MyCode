#include <stdio.h>

int main()
{
	setvbuf(stdout,NULL,_IONBF,0);
	printf("hello");
	//fflush(stdout);
	//fclose(stdout);
	int i =0;
	//while(i++<1024)
	//{
	//	printf(" ");
	//}
}
