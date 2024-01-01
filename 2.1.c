#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/types.h"
void main(){
int pid1,pid2;
//printf("a");
pid1 = fork();
if(pid1<0){
printf("create pid1 failed");
}else if(pid1==0){
printf("current pid: %d, father pid: %d b\n",getpid(),getppid());
}else{
pid2 = fork();
	if(pid2<0){
	printf("create pid1 failed");
	}else if(pid2 == 0){
	printf("current pid: %d, father pid: %d c\n",getpid(),getppid());
	}else{
	printf("current pid: %d,a\n",getpid());
	}
}
}