/*两个读者一个写者BUFF6*/

#include "my.h"

int fd;
static int wj=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
char buf[100];
int loop=0;

void *worker1(void * arg)
{
	int r=0,j;
	time_t t;
	while(loop<1000)
	{
		if(wj==0)
		{
			t = time(0);
			sprintf(buf,"worker 1 :%d %s",rand()%1000,ctime(&t));
			write(fd,buf,strlen(buf));
			fsync(fd);
			pthread_mutex_lock(&mutex);
			wj=1;
			pthread_mutex_unlock(&mutex);
			
		}
	}
}

void *worker2(void * arg)
{
	int r=0,j=0;
	time_t t;
	while(loop<1000)
	{
		if(wj == 1)
		{
			loop++;
			sprintf(buf,"worker 2 :%d %s",rand()%10000+10000,ctime(&t));
			write(fd,buf,strlen(buf));
			fsync(fd);
			
			pthread_mutex_lock(&mutex);
			wj=0;
			pthread_mutex_unlock(&mutex);
			
		}
	}
	exit(-1);
}

void *worker3(void * arg)
{
	int r=0,j=0;
	while(1)
	{
		
	}
}

int main()
{
	int ret;
	pthread_t tid[3];
	pthread_mutex_init(&mutex,NULL);
	srand(time(NULL));
	fd = open("mydata.txt",O_RDWR|O_TRUNC |O_CREAT,0666);
	
	ret=pthread_create(&tid[0],NULL,worker1,NULL);
	if(ret)
	{
		perror("thread1 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[1],NULL,worker2,NULL);
	if(ret)
	{
		perror("thread2 failed\n");
		exit(1);
	}
	ret=pthread_create(&tid[2],NULL,worker3,NULL);
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
