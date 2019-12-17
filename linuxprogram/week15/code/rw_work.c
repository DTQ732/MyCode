/*两个读者一个写者BUFF6*/

#include "my.h"

static int buff[6];
static int wi=0,ri=0;
static space=6;
pthread_mutex_t mutex;

void *reader1(void * arg)
{

}

void *reader1(void * arg)
{

}

void *writer(void * arg)
{

}

int main()
{
	int ret;
	pthread_t tid[3];
	pthread_mutex_init(&mutex,NULL);
	ret=pthread_create(&tid[0],NULL,reader1,(void*)&p);
	if(ret)
	{
		perror("thread1 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[1],NULL,reader2,(void*)&p);
	if(ret)
	{
		perror("thread2 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[2],NULL,writer,(void*)&p);
	if(ret)
	{
		perror("thread2 failed\n");
		exit(1);
	}
}
