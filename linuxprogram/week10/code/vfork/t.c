#include "h.h"

static void callback1(){
	printf("--------callback1---------\n");
}

static void callback2(){
        printf("--------callback2---------\n");
}

static void __attribute__ ((constructor)) before_main(){
	printf("--------constructor--------\n");
}

static void __attribute__ ((destructor)) after_main(){
        printf("--------constructor--------\n");
}

int main(int argc,char*argv[])
{
	atexit(callback1);
	atexit(callback2);
	FILE*fp;
	char buf[]="test data from full buffer!\n";
	if((fp=fopen("test.dat","w"))==NULL)
	{
		perror("failed to fopen!\n");
		return -1;	
	}

	if (fputs(buf,fp)==EOF)
	{
		perror("failed to fputs\n");
	}
	printf("printf:data from line buffer");
	
	if(argc & 1) _exit(0);
	switch(argv[1][0])
	{
	case '0':exit(0);
	case '1':_exit(0);
	case '2':return 0;
	}
}
