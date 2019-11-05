#include "func.h"
#include "meun.h"

void start()
{
	void (*pmeun)();
	void * hd =dlopen("./libmeun.so",RTLD_LAZY);
	if (!hd){
		fprintf(stderr,"%s\n",dlerror());
		exit(-1);
	}
	pmeun =dlsym(hd,"meun");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}
	pmeun();
}

int main()
{
	start();
}
