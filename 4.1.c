#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int arr[2];
sem_t lock;
sem_t lockr;
sem_t locko;
int a = 0;

void read1(){
	FILE*fp = fopen("1.dat","r");
	int x;
	while(fscanf(fp,"%d",&x)!=EOF){
		sem_wait(&lockr);
		
		sem_wait(&lock);
		arr[a] = x;
		a = (a + 1) % 2;
		sem_post(&lock);
		if(a == 1){
		sem_post(&lockr);	
		}else{
		sem_post(&locko);
		}
		
	}
}
void read2(){
	FILE*fp = fopen("2.dat","r");
	int x;
	while(fscanf(fp,"%d",&x)!=EOF){
		sem_wait(&lockr);
		
		sem_wait(&lock);
		arr[a] = x;
		a = (a + 1) % 2;
		sem_post(&lock);
		if(a == 1){
		sem_post(&lockr);	
		}else{
		sem_post(&locko);
		}
		
	}
}
void operate1(){
	while(1){
	sem_wait(&locko);
	
	printf("add: %d + %d = %d\n",arr[0],arr[1],arr[0]+arr[1]);
	
	sem_post(&lockr);
	}
}
void operate2(){
	while(1){
	sem_wait(&locko);

	printf("mul: %d * %d = %d\n",arr[0],arr[1],arr[0]*arr[1]);

	sem_post(&lockr);
	}
}

int main(){
	int ret1, ret2, ret3, ret4;
	pthread_t id1, id2, id3, id4;
	
	
	sem_init(&lockr, 0, 1);
	sem_init(&locko, 0, 0);
	sem_init(&lock, 0, 1);

	
	ret1 = pthread_create(&id1, NULL, (void*)read1, NULL);
	if(ret1){
		printf("Create 1 error!\n");
	}
	ret2 = pthread_create(&id2, NULL, (void*)read2, NULL);
	if(ret2){
		printf("Create 2 error!\n");
	}
		
	ret3 = pthread_create(&id3, NULL, (void*)operate1, NULL);
	if(ret3){
		printf("Create 3 error!\n");
	}
	ret4 = pthread_create(&id4, NULL, (void*)operate2, NULL);
	if(ret4){
		printf("Create 4 error!\n");
	}

	
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	pthread_join(id4, NULL);
	
	return 0;
}