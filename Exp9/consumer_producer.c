//To make sure that the producer won’t try to add data into the buffer if it’s full 
//and that the consumer won’t try to remove data from an empty buffer.

#include<stdio.h>
#include<stdlib.h>

//the semaphore is mutex variable.

int mutex = 1, full = 0 , empty = 3, x = 0;
int wait(int s){	
	return (--s);
}
int signal(int s){
	return (++s);
}
void producer(){
	mutex = wait(mutex);
	full = signal(full);
	empty = wait(empty);
	x++;
	printf("\nProducer produces the item %d", x);
	mutex = signal(mutex);
}
void consumer(){
	mutex=wait(mutex);
	full=wait(full);
	empty=signal(empty);
	printf("\nConsumer consumes item %d",x);
	x--;
	mutex=signal(mutex);
}

int main(){
	printf("Hello Consumer Producer Problem using Semaphores\n");

	int n;

	printf("\n1.Producer\n2.Consumer\n3.Exit");
	while(1){
		printf("\nEnter your choice: ");
		scanf("%d",&n);
		switch(n){
			case 1: 
				if(mutex == 1 && empty!=0)
					producer();
				else
					printf("Buffer is full!\n");
			break;
			case 2: 
				if(mutex == 1 && full!=0)
					consumer();
				else
					printf("Buffer is empty!\n");
			break;
			case 3:
				exit(0);
			break;
			
		}
	}
	return 0;
}
