//---------------------------------------------------------
//
//	Desc: A server program that fork a new process and then 
//			run a client program on that process.
//
//	Date: 29/1/2018
//
//	Author: VU DUY DU - 2k16/CO/364
//
//---------------------------------------------------------

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
	printf("Main process has id: %i\n",getpid());
	int p = fork();
	if(p==0){//we want the child to do this task only
		printf("Child: I am a child process, my ID is: %i\n",getpid());
		printf("Child: Now I'm gonna run a client program inside of me (clientprogram.out)\n");
		//make sure client program is in the same directory with server
		char* argv[2] = {"Not null",NULL};
		//using execvp() from exec family to execute client program
		execvp("./clientprogram",argv);
		printf("Child: client's code is merge with this child code\n");
	}else{//at this point p is equal to the child process id is allowed
		printf("Parent: Hello child, I'm your parent %i, I have your ID: %i\n",getpid(),p);
		printf("Parent: Paused to wait for all the children to terminate\n");
		wait(NULL);//wait for all the children
		printf("Parent: All children have terminated\n");
	}
	return 0;
}
