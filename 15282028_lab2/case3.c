#include <stdio.h>
#include <stdlib.h>
int main(){
  int p1,p2,p3,p4,p5;
  while ((p1=fork())==-1);
    if(!p1){
      printf("parent with pid %d,parent pid%d.\n",getpid(),getppid());
      while((p2=fork())==-1);
         if(!p2){
         printf("child2 with pid %d,parent pid%d.\n",getpid(),getppid());
while((p4=fork())==-1);
if(!p4){
            printf("child4 with pid %d,parent pid%d.\n",getpid(),getppid());
exit(0);}
else
wait(0);
while((p5=fork())==-1);
if(!p5){
            printf("child5 with pid %d,parent pid%d.\n",getpid(),getppid());
exit(0);}
else
wait(0);

exit(0);
}
else
wait(0);
while ((p3=fork())==-1);
if(!p3){
            printf("child3 with pid %d,parent pid%d.\n",getpid(),getppid());
exit(0);}
else
wait(0);

exit(0);
}
else
wait(0);
return 0;
}

