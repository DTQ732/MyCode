/**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <error.h>
#include <pthread.h>
#include <semaphore.h>

int writerj=0;
int loop = 0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int main()
{
	int ret,r[3],status;
	pthread_mutex_init(&mutex,NULL);
	
	int i = 0;
	for(;i<3;i++){
		r[i] = fork();
		if(r[i]==0)
			break;
		if(r[i]<0) exit(-1);
	}
	
	//work1
	if(i==0){
		printf("fork %d\n",i);
		
		while(loop<10)
		{
			
			if(writerj==0){
				pthread_mutex_lock(&mutex);
				writerj=1;
				pthread_mutex_unlock(&mutex);
				loop++;
				printf("writer %d\n",writerj);
			
			}
			
		}
		
		exit(-1);
	}
	
	//work2
	if(i==1){
		printf("fork %d\n",i);
		
		while(loop<10)
		{	
			
			if(writerj==1){
				pthread_mutex_lock(&mutex);
				writerj=0;
				pthread_mutex_unlock(&mutex);
				printf("writer %d\n",writerj);
				loop++;
			}
		}
		exit(-1);
	}
	
	//work3
	if(i==2){
		//printf("work %d\n",r[i]);
		exit(-1);
	}
	
	
	
	for(int j=0;j<3;j++){
		//printf("work %d\n",r[j]);
		waitpid(r[j],&status,0);
	}
	return 0;
}
