#include <stdio.h>
#include <pthread.h>

void *myThread1(void *arg1){
	int *num;
	num = (int*)arg1;
	printf("%d \n",*num);
	return (void*)0;
}

void *myThread2(void *arg2){
	char *chr;
	chr = (char*)arg2;
	printf("%c \n",*chr);
	return (void*)0;
}

int main(){
	int ret1, ret2;
	pthread_t t1,t2;
	int test1 = 4;
	char test2 = 'c';
	int *attr1 = &test1;
	char *attr2 = &test2;
	ret1 = pthread_create(&t1, NULL, myThread1, (void*)attr1);
	if (ret1)
		{
		printf("Create error!\n");
		}

	ret2 = pthread_create(&t2, NULL, myThread2, (void*)attr2);
	if (ret2)
		{
		printf("Create error!\n");
		}
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}