#include "my.h"

int c = 100;
pthread_mutex_t mutex;

void *worker(void*arg)
{
	int pt=*(int*)arg;
	printf("pthread %d\n",pt);
}

int main()
{
	int ret;
	int p=1;
	pthread_t tid[2];
	pthread_mutex_init(&mutex,NULL);
	ret=pthread_create(&tid[0],NULL,worker,(void*)&p);
	if(ret)
	{
		perror("thread1 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[1],NULL,worker,(void*)&p);
	if(ret)
	{
		perror("thread2 failed\n");
		exit(1);
	}
	pthread_join(tid[0],NULL);
}
