#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
        pid_t p1,p2,p3;
        p1=fork();//
        int i=0;
        if(p1<0)
        {
                printf("pid is %d,error\n！",getpid());
        }
        if(p1==0)
{
		p2=fork();
		if(p2>0)
			p3=fork();
		pid_t p,pp;
		p=getpid();
		pp=getppid();
		while(i<100)
		{
			printf("my pid is %d，my father's pid is %d\n",p,pp);
			i=i+1;
			sleep(1);
			if(p3>0 && p2>0 && i>10)
			{
				int *p;//定义一个野指针，产生段错误
				*p=1;
			}
		}
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
