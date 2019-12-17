#include "my.h"
static int share = 0;
static pthread_rwlock_t rwlock;

#undef WRITER_FIRST
void *reader(void*param)
{
	int i =(int)param;
	while(1){
		pthread_rwlock_rdlock(&rwlock);
		fprintf(stderr,"reader--%d:the share = %d\n",i,share);
		pthread_rwlock_unlock(&rwlock);
	}
	return NULL;
}
void *writer(void*param)
{
	int i =(int)param;
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		share++;
		fprintf(stderr,"writer--%d:the share = %d\n",i,share);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid[TN];
	pthread_rwlockattr_t rwlock_attr;
	pthread_rwlockattr_init(&rwlock_attr);
	
	#ifdef WRITER_FIRST
		pthread_rwlockattr_setkind_np(&rwlock_attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
	#endif
	pthread_rwlock_init(&rwlock,&rwlock_attr);
	int i=0,ret=0;
	pthread_rwlock_rdlock(&rwlock);
	for(i=0;i<TN;i++)
	{
		if(i%2==0)
		{
			ret=pthread_create(&tid[i],NULL,reader,(void*)i);
		}
		else
		{
			ret=pthread_create(&tid[i],NULL,writer,(void*)i);
		}
		
		if(ret)
		{
			perror("thread2 failed\n");
			exit(i);
		}
	}
	pthread_rwlock_unlock(&rwlock);
	while(i-->0)
	{
		pthread_join(tid[i],NULL);
	}
	
	pthread_rwlockattr_destroy(&rwlock_attr);
	pthread_rwlock_destroy(&rwlock);
}
