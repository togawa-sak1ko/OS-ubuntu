#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/types.h"
void main(){
int pid1,pid2;
int i,j,k;
pid1 = fork();
if(pid1<0){
printf("create pid1 failed");
}else if(pid1==0){
//printf("current pid: %d, father pid: %d b\n",getpid(),getppid());
	for(i=0;i<1000;i++){
	printf("b");
	}
}else{
pid2 = fork();
	if(pid2<0){
	printf("create pid1 failed");
	}else if(pid2 == 0){
	//printf("current pid: %d, father pid: %d c\n",getpid(),getppid());
	for(j=0;j<1000;j++){
	printf("c");
	}
	}else{
	//printf("current pid: %d,a\n",getpid());
	for(k=0;k<1000;k++){
	printf("a");
	}
	}
}
}