/*两个读者一个写者BUFF6*/

#include "my.h"

static int buff[6];
static int wi=0,ri=0;
static int space=6;
int writerj=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void *reader1(void * arg)
{
	int r=0,j;
	while(1)
	{
		if(space <= 5)
		{
			pthread_mutex_lock(&mutex);
			r = buff[(ri++)%6];
			j = ri-1;
			space++;
			pthread_mutex_unlock(&mutex);
			fprintf(stdout,"reader1 read %d form %d\n",r,j%6);
			pthread_yield();
			sleep(1);
		}
	}
}

void *reader2(void * arg)
{
	int r=0,j=0;
	while(1)
	{
		if(space <= 5)
		{
			pthread_mutex_lock(&mutex);
			r = buff[(ri++)%6];
			j=ri-1;
			space++;
			pthread_mutex_unlock(&mutex);
			fprintf(stdout,"reader2 read %d form %d\n",r,j%6);
			pthread_yield();
			sleep(1);
		}
	}
}

void *writer(void * arg)
{
	int r=0,j=0;
	while(1)
	{
		if(space >0)
		{
			pthread_mutex_lock(&mutex);
			r = buff[(wi++)%6]=writerj++;
			j= wi-1;
			space--;
			pthread_mutex_unlock(&mutex);
			fprintf(stdout,"writer write %d to %d\n",r,j%6);
			pthread_yield();
			sleep(1);
		}
	}
}

int main()
{
	int ret;
	pthread_t tid[3];
	pthread_mutex_init(&mutex,NULL);
	ret=pthread_create(&tid[0],NULL,reader1,NULL);
	if(ret)
	{
		perror("thread1 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[1],NULL,reader2,NULL);
	if(ret)
	{
		perror("thread2 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[2],NULL,writer,NULL);
	if(ret)
	{
		perror("thread2 failed\n");
		exit(1);
	}
	for(ret=0;ret<3;ret++)
	{
		pthread_join(tid[ret],NULL);
	}
}
