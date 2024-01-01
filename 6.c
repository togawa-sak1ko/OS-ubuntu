#include <stdio.h>
#include <signal.h>
#include<unistd.h>
#include <stdlib.h>

static void sig_usr(int signo)
{
	printf("received signal %d\n", signo);
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
}
static void sig_int(int sigint)
{
	printf("received signal %d\n", sigint);
	if (sigint == SIGINT)
		printf("received SIGINT\n");
}
int main(void)
{
	int pid;
	pid = fork();
	if(pid < 0){
		printf("create pid failed");
	}else if(pid == 0){
		printf("child's pid =%d\n", getpid());
		if (signal(SIGINT, sig_int) == SIG_ERR)
		{
			printf("can't catch SIGINT\n");
			exit(1);
		}
		for(;;);
	}else{
	printf("fateher's pid = %d\n", getpid());
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
	{
		printf("can't catch SIGUSR1\n");
		exit(1);
	}
	for(;;);
	}
}
