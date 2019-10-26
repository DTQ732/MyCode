#include "func.h"
#include "meun.h"

void start()
{
	void (*meun)();
	void * hd =dlopen("./libmeun.so",RTLD_LAZY);
	if (!hd){
		fprintf(stderr,"%s\n",dlerror());
		exit(-1);
	}
	meun =dlsym(hd,"meun");
	if (dlerror() != NULL) {
		fprintf(stderr,"%s\n",dlerror());
		exit(-2);
	}
	meun();
}

int main()
{
	start();
}
