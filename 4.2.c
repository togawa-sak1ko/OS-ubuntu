#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int arr[2];
int a = 0;
int counter = 0;

sem_t r1, r2, o1, o2;

void read1(){

	FILE*fp = fopen("1.dat","r");
    	while(1){
        
	sem_wait(&r1);	
        fscanf(fp,"%d",&arr[a]);
        a = (a + 1) % 2;
        sem_post(&r2);

        char c11 = fgetc(fp);
        if(c11=='\n' || c11==EOF) break;
    }

}

void read2(){

	FILE*fp = fopen("2.dat","r");
    	while(1){
        sem_wait(&r2);
        fscanf(fp,"%d",&arr[a]);  
        a = (a + 1) % 2;       
        if(counter==0){
        	counter = 1;
        	sem_post(&o1);
        }
        else{
        	counter = 0;
        	sem_post(&o2);
        }

        char c11 = fgetc(fp);
        if(c11=='\n' || c11==EOF) break;
    }

}

void operate1(){
	
	while(1){	
    	
    	sem_wait(&o1);
    	
    	printf("add: %d + %d = %d\n",arr[0],arr[1],arr[0]+arr[1]);
    	
    	sem_post(&r1);
    	
    }   
}

void operate2(){
	
	while(1){	
    		
    	sem_wait(&o2);
    	
    	printf("mul: %d * %d = %d\n",arr[0],arr[1],arr[0]*arr[1]);
    	
    	sem_post(&r1);
    	
    }   
}

int main(){
	pthread_t id1, id2, id3, id4;
	
	sem_init(&r1,0,1);
	sem_init(&r2,0,0);
	sem_init(&o1,0,0);
	sem_init(&o2,0,0);
	
	pthread_create(&id1, NULL, (void *)read1, NULL);
	pthread_create(&id2, NULL, (void *)read2, NULL);
	pthread_create(&id3, NULL, (void *)operate1, NULL);
	pthread_create(&id4, NULL, (void *)operate2, NULL);
	
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	pthread_join(id4, NULL);
	
	return 0;
}