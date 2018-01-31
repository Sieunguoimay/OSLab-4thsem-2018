//exp1b-2.c
//-----------------------------------------------------------------
//
//	this program create 5 child processes from the parent process,
//	the parent process has all the ids of its children.
//
//-----------------------------------------------------------------	

#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#define BUF_SIZE 100
int main(){
	//execute the command 'ps' under Shell
	system("ps");
	
	int count = 1;
	//at this point program is forked into with the same data
	int p1 = fork();
	//fork return id of the child, if any, otherwise 0
	//in parent process, p assingned with the id of the child	
	if(p1!=0){
		//fork for the second time in parent process
		int p2 = fork();
		if(p2!=0){
			//fork for the third time in parent process
			int p3 = fork();
			if(p3!=0){
				//fork for the fouth time in parent process
				int p4 = fork();
				if(p4!=0){
					//fork for the fifth time in parent process
					int p5 = fork();
					if(p5!=0){
						printf("%i: %i is parent of %i, %i ,%i ,%i and %i\n",count,getpid(),p1,p2,p3,p4,p5);
					}else{
						count++;
						printf("%i: %i is parent of %i\n",count,getpid(),p5);			
					}
				}else{
					count++;
					printf("%i: %i is parent of %i\n",count,getpid(),p4);			
				}
			}else{
				count++;
				printf("%i: %i is parent of %i\n",count,getpid(),p3);			
			}
		}else{
			count++;
			printf("%i: %i is parent of %i\n",count,getpid(),p2);
		}
	}else{//in child process, p assingned with 0	
		count++;
		printf("%i: %i is parent of %i\n",count,getpid(),p1);
	}

	return 0;
}
