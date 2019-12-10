#include "my.h"

int main()
{
	int i=0;
	sigset_t blockall_mask;
	sigset_t empty_mask;
	
	printf("%s PID is %d\n",argv[0],getpid());
	
	for(i=1;i<NSIG;i++)
	{
		if (i==SIGKILL || i==SIGSTOP || i ==32 || i ==33)
			continue;
		if (signal(i,&handler)==SIG_ERR)
		{
			fprintf(stderr,"signal for signo(%d) failed (%s)\n",i,strerror(errno));
		}
	}
	if (argc > 1)
	{
		int sleep_time = atoi(argv[1]);
		sigfillset(&blockall_mask);
		if(sigprocmask(SIG_SETMASK,&blockall_mask,NULL)==-1)
		{
			fprintf(stderr,"setpromasks to block all signal failed (%s)\n",strerror(errno));
			return -2;
		}
		
		printf("I will sleep %d s\n",sleep_time);
		
		sleep(sleep_time);
		sigemptyset(&empty_mask);
		if (sigprocmask(SIG_SETMASK,&empty_mask,NULL)==-1)
		{
			fprintf(stderr,"setpromasks to release all signal failed (%s)\n",strerror(errno));
			return -3;
		}
			
	}
	
	while(!getSIGINT)
		continue;
		
	printf("%-10s%-10s\n","signo","times");
	
	for(int i=1;i<NSIG;i++)
	{
		if(sig_cnt[i]!=0)
		{
			printf("%-10d %-10d\n",i,sig_cnt[i]);
		}
	}	
	
	return 0;
		
}
