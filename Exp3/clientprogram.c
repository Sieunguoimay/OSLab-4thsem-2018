//---------------------------------------------------------
//
//	Desc: A client program that do some cool thing
//
//	Date: 29/1/2018
//
//	Author: VU DUY DU - 2k16/CO/364
//
//---------------------------------------------------------
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
int main(){
	printf("Client: Hello world from client with process id:%i,\
 which is execute from server %i\n",getpid(),getppid());
	int n;
	printf("Client: Enter a number: ");
	scanf("%d",&n);
	printf("Client: Printing n: ");
	//this is a n-cycle loop that display a set of number from 0 to n-1
	for(int i = 0; i<n; i++)
		printf("%i ",i);
	printf("\n");
	return 0;
}
