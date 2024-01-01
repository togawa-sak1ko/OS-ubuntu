#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>

char arr[100];

int main(){
	int pid1,pid2;
	pid1 = fork();
	if(pid1<0){
		printf("create pid1 failed");
		return -1;
		}else if(pid1==0){
		int qid1 = msgget(1, IPC_CREAT | 0666);
		while(1){
			msgrcv(qid1, &arr, sizeof(arr), 0, MSG_NOERROR);
			printf("input is: %s\n", arr);
		}
		}else{
		pid2 = fork();
			if(pid2<0){
			printf("create pid1 failed");
			return -1;
			}else if(pid2 == 0){
				int qid2 = msgget(1,IPC_CREAT | 0666);
				while(1){
				fgets(arr,sizeof(arr),stdin);
				if(strncmp(arr,"exit",4)==0){
					msgctl(qid2, IPC_RMID, 0);
					kill(pid1,SIGKILL);
					kill(pid2,SIGKILL);
					}
				msgsnd(qid2, &arr, sizeof(arr), IPC_NOWAIT);	
				}
				
				
			}else{
				wait(pid1);
				wait(pid2);
			}
	}
	return 0;
}