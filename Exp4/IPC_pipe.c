#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
//pipe from parent to child, parent write to pp2c[1]
//then child read from pp2c[0]
int pp2c[2];
//pipe from child to parent, child write to pc2p[1]
//then parent read from pc2p[0]
int pc2p[2];

void child_process(){
	printf("Welcome to child process\n");
	close(pp2c[1]);

	printf("Child: connect pp2c[0] to stdin\n");	
	//connect pp2c[0] to stdin
	dup2(pp2c[0],STDIN_FILENO);
	close(pp2c[0]);
	//connect pc2p[1] to stdout
	close(pc2p[0]);
	dup2(pc2p[1],STDOUT_FILENO);//it stops here??
	close(pc2p[1]);

	printf("Child: execute rev\n");	
	execlp("rev","rev",(char*)NULL);
	//exit with code 127 if exec fails
	perror("exec failed");
	exit(127);
}
void parent_process(){

	printf("Welcome to parent process\n");
	close(pp2c[0]);
	close(pc2p[1]);

	printf("Parent: open pipes as stream\n");
	//open pipes as stream
	FILE*out = fdopen(pp2c[1],"w");
	FILE*in = fdopen(pc2p[0],"r");
	
	char word[1024];
	//redirect input to child process
	printf("Parent: redirect input to child process\n");

	if(scanf("%s",word)){//it stops here..
		fprintf(out,"%s\n",word);
	}
	fclose(out);
	//read child process output
	printf("Parent: read child process output");
	while(fscanf(in,"%s",word)!=EOF){
		printf("%s\n",word);
	}
	fclose(in);

	//call wait on exited child
	wait(NULL);
}

int main(){
	printf("Hello experiment 4 - Interprocess Communication using pipe method\n");

	pipe(pp2c);
	pipe(pc2p);	

	switch(fork()){
		case -1:
			break;
		case 0:
			child_process();
			break;
		default:
			parent_process();
			break;
	}
	return 0;
}
