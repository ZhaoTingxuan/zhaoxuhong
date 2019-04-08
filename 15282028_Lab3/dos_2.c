#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
volatile int ticketCount=1000;
sem_t *flag=NULL;
void *SaleThread(void *arg)
{
	int num,temp;
	num=atoi(arg);
	for(int i=0;i<num;i++)
	{
		if(i % 10 ==0)
			printf("sold%dtickets,remain%dtickets\n",i,ticketCount);
		sem_wait(flag);
		temp=ticketCount;
		pthread_yield();
		temp=temp-1;
		ticketCount-=1;
		pthread_yield();
		ticketCount=temp;
		sem_post(flag);
	}
	return NULL;
}

void *RefundThread(void *arg)
{
	int num,temp;
	num=atoi(arg);
	for(int i=0;i<num;i++)
	{
		if(i % 10 ==0)
			printf("returned%dtickets,remain%dtickets\n",i,ticketCount);
		sem_wait(flag);
		temp=ticketCount;
		pthread_yield();
		temp=temp+1;
		ticketCount+=1;
		pthread_yield();
		ticketCount=temp;
		sem_post(flag);
	}
	return NULL;
}
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("请正确输入参数！\n");
		exit(0);
	}
	flag=sem_open("flag",O_CREAT,0666,1);
	printf("the beginning：%d\n",ticketCount);
	pthread_t p1,p2;
	printf("%s %s",argv[1],argv[2]);
	pthread_create(&p1,NULL,SaleThread,argv[1]);
	pthread_create(&p2,NULL,RefundThread,argv[2]);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printf("the final：%d\n",ticketCount);
	sem_close(flag);
	sem_unlink("flag");
	return 0;

}
