#include <stdio.h>
#include <pthread.h>

void *myThread1(void *arg1){
	int *num;
	num = (int*)arg1;
	int sum = 0;
	int i, k;
	for(i = 0;i < 1000;i++){
		sum+=num[i];
	}
	printf("sum: ");
	printf("%d \n",sum);
	return (void*)0;
}

void *myThread2(void *arg2){
	int *arr = (int*)arg2;
	int i,j,k;
	for(i = 0;i < 1000;i++){
		for(j = i;j < 1000;j++){
			int temp;
			if(arr[i]<arr[j]){
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	printf("list: ");
	for(k = 0;k<1000;k++){
		printf("%d ",arr[k]);
	}
	return (void*)0;
}

int main(){
	int ret1, ret2;
	pthread_t t1,t2;
	int test1[1000];
	int i, j;
	for(i = 0;i < 100;i++){
		for(j = 0;j < 10;j++){
			test1[i*10+j]=j+1;
		}
	}
	int *attr1 = &test1;
	ret1 = pthread_create(&t1, NULL, myThread1, (void*)attr1);
	if (ret1)
		{
		printf("Create error!\n");
		}

	ret2 = pthread_create(&t2, NULL, myThread2, (void*)attr1);
	if (ret2)
		{
		printf("Create error!\n");
		}
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}