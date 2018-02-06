//------------------------------------------------------------------------------
//
//	Desc: Pipe communication between child process and parent process. Child asks
//			parent for the file, and parent sends back the file content.
//
//	Date: 6/2/2018
//
//	Author: VU DUY DU - 2k16/CO/364
//
//------------------------------------------------------------------------------

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define MAXSIZE 10000

void write_to_console(const char s[]){
		write(1,s,strlen(s));
}
typedef struct two_way_pipe{
	int pc2p[2];//child write at pc2p[1], parent read at pc2p[0]
	int pp2c[2];
}Pipe;
void initPipe(Pipe*p){
	if(pipe(p->pc2p)<0){	
		write_to_console("Init: failed to initialize pipe pc2p\n");
		return ;
	}
	if(pipe(p->pp2c)<0){	
		write_to_console("Init: failed to initialize pipe pp2c\n");
		return;
	}
}
void run_parent(Pipe*p){
	write_to_console("P: Hello from Parent process\n");

	//get file name sent from child process
	char buf;//read one by one
	char filename[26];
	close(p->pc2p[1]);//close the other unused terminal
	while(read(p->pc2p[0],&buf,1)){
		filename[strlen(filename)]=buf;
		filename[strlen(filename)+1]='\0';
	}
	close(p->pc2p[0]);
	write_to_console(filename);
	write_to_console(" --(received by Parent)\n");


	//load the file from system
	char buffer[MAXSIZE] = "File does not exit";
	FILE*file = fopen(filename,"r");
	if(file){
		const int MAX_NUM_CHAR_PER_LINE = 100;
		char line[MAX_NUM_CHAR_PER_LINE];
		strcpy(buffer,"");
		while(fgets(line,MAX_NUM_CHAR_PER_LINE,file)){
			//write(1,line,strlen(buffer));
			strcat(buffer,line);
		}
		write_to_console("P: Success to load the file ");
	}else{
		write_to_console("P:Error: Failed to load the file ");
	}	
	write_to_console(filename);
	write_to_console("\n");

	//send buffer data to the client
	close(p->pp2c[0]);
	write(p->pp2c[1],buffer,strlen(buffer));
	close(p->pp2c[1]);
}
void run_child(Pipe*p){
	write_to_console("C: Hello from Child process\n");

	//send file name to parent
	write_to_console("C: Sending file name to parent\n");
	close(p->pc2p[0]);
	const char filename[]="README.txt";
	write(p->pc2p[1],filename,strlen(filename));
	close(p->pc2p[1]);
	
	//get the parent file content
	char buffer[MAXSIZE],buf;
	int size = 0;
	close(p->pp2c[1]);
	while(read(p->pp2c[0],&buf,1)){
		buffer[size++] = buf;
		buffer[size] = '\0';
	}
	write_to_console("C: Received the data: \n\"");	
	write_to_console(buffer);
	write_to_console("\"\n");

}
int main(){
	printf("Hello world of IPC\n");

	//create a two_way_pipe for communication
	Pipe p;
	initPipe(&p);
	
	switch(fork()){//fork a new child
		case -1:
			write_to_console("error: failed to fork a child process\n");
		break;
		case 0:
			//this is child process
			run_child(&p);
		break;
		default:
			//this is parent process
			run_parent(&p);
		break;
	}
	return 0;
}
