#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>
#include<string>

#define LOOP_NUM 3
sem_t semaphore;
int item;

void* consumer_thread(void*arg){
	printf("\nConsumer Thread Entered\n\n");
	for(int i = 0; i < LOOP_NUM; i++){
		//wait
		sem_wait(&semaphore);
		printf("\nConsumer: Entered...\n");
	
		//critical Section
		sleep(2);
		//item --;
		std::cout<<"Consumer: Accessed item "<<item<<"\n";

		//signal
		printf("Consumer: Just Exiting...\n");
		sem_post(&semaphore);
		sleep(1);
	}
	return NULL;
}
void* producer_thread(void*arg){
	printf("\nProducer thread Entered\n\n");
	for(int i = 0; i < LOOP_NUM; i++){
		//wait
		sem_wait(&semaphore);
		printf("\nProducer: Entered...\n");
	
		//critical Section
		sleep(2);
		item ++;
		std::cout<<"Producer: Producted item "<<item<<"\n";

		//signal
		printf("Producer: Just Exiting...\n");
		sem_post(&semaphore);
		sleep(1);
	}
	return NULL;
}

int main(){
	printf("hello semaphore ");
	std::cout<<sem_init(&semaphore, 0,1);
	
	//create 2 threads for consumer and producer
	pthread_t t1,t2;
	pthread_create(&t1,NULL,producer_thread,NULL);
	pthread_create(&t2,NULL,consumer_thread,NULL);

	//threads are done their jobs
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	//destroy the semaphore
	sem_destroy(&semaphore);
	return 0;
}

