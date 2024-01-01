#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/types.h"

int main(){
int pid1,pid2;
int filedis[2];
char a[30] = "child 1 is sending a message";
char b[30] = "child 2 is sending a message";
char c[30];
pipe(filedis);

pid1 = fork();
if(pid1<0){
	printf("create pid1 failed");
	return -1;
	}else if(pid1==0){
	close(filedis[0]);
	write(filedis[1],a,30);
	}else{
	pid2 = fork();
		if(pid2<0){
		printf("create pid1 failed");
		return -1;
		}else if(pid2 == 0){
		close(filedis[0]);
		write(filedis[1],b,30);
		}else{
		close(filedis[1]);
		read(filedis[0],c,30);
		printf("%s\n",c);
		close(filedis[1]);
		read(filedis[0],c,30);
		printf("%s\n",c);
		}
}
return 0;
}