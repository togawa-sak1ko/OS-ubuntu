#include <stdio.h>
#include <pthread.h>

void myThread1(){
	printf("myThread1\n");
}

void myThread2(){
	printf("myThread2\n");
}

int main(){
	int ret1, ret2;
	pthread_t t1,t2;
	
	ret1 = pthread_create(&t1, NULL, (void*)myThread1, NULL);
	if (ret1)
		{
		printf("Create error!\n");
		}

	ret2 = pthread_create(&t2, NULL, (void*)myThread2, NULL);
	if (ret2)
		{
		printf("Create error!\n");
		}
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}