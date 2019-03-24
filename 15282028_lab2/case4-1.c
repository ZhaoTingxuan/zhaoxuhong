#include<stdio.h>
#include<unistd.h>
int main()
{
	pid_t p1,p2;
	p1=fork();
	if(p1<0)
	{
		printf("my pid is %d,error\n！",getpid());	
	}
	if(p1==0)
	{
		p2=fork();
		if(p2>0)
			fork();
		pid_t;
	        while(1)
	{
			printf("my pid is %d，my father's pid is %d\n",getpid(),getppid());
			sleep(1);
	}
		sleep(1);


	}
	if(p1>0)
	{
		fork();
		pid_t;
		while(1)
	{
			printf("my pid is %d，my father's pid is %d\n",getpid(),getppid());
			sleep(1);
	}
		sleep(1);
	}
	return 0;
}
