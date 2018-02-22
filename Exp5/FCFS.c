#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#define MAX_NUM 100
void write_to_console(const char s[]){
		write(1,s,strlen(s));
}
char temp[1000];
int pc2p[2];
int pp2c[2];


int main(){
	printf("Helo FCFS simulation\nEnter no of processes: ");
	int n = 2,i;//number of processes to be scheduled
	scanf("%d",&n);
	int arr_time[MAX_NUM] = {0,2};
	int burst_time[MAX_NUM] = {3,4};
	int the_processed[MAX_NUM];
	printf("Arrive time and Burst time of: \n");
	for(i = 0; i<n; i++){
		printf("process %i: ",i);
		scanf("%d %d",&arr_time[i],&burst_time[i]);
		the_processed[i]=0;
	}
	for(i = 0; i<n; i++)
		printf("%d\t%d\n",arr_time[i],burst_time[i]);

	int scheduling_time = 0;
	
	//create 2 pipes
	

	double awt = 0.0;
	double atat = 0.0;
	int processed_num = 0;
	while(processed_num<n){//wait for the job to come
		//determine the index of unprocessed process which has the min_arr_time 
		int process_index = -1;
		int min_arr_time = 1000000;
		for(i = 0; i<n; i++){
			if(!the_processed[i])//unprocessed
			if(arr_time[i]<min_arr_time){
				min_arr_time = arr_time[i];
				process_index = i;
			}
		}
		//if a new process is comming
		if(process_index>=0&&min_arr_time<=scheduling_time){
			printf("P-%d: A new process is comming\n",getpid());
			pipe(pp2c);
			pipe(pc2p);
			switch(fork()){
				case -1: printf("Error to fork a child\n");break;
				case 0:
					//run the child here
					sprintf(temp,"\nC-%d: Enter child process, ready to run\nC-%d: ",getpid(),getpid());
					write_to_console(temp);
					//receive burst time
					close(pp2c[1]);
					char buffer[2];int btime = 0;
					while(read(pp2c[0],&buffer[0],1)){
						btime*=10;
						btime+= buffer[0]-'0';
					}
					int time = 0;
					while(time<btime){
						sleep(1);
						time++;
						sprintf(temp,"%d ",time);
						write_to_console(temp);
					}
					sprintf(temp,"\nC-%d: Finished, now sending back my running time\n\n",getpid());
					write_to_console(temp);
					close(pc2p[0]);
					sprintf(buffer,"%d",time);
					write(pc2p[1],buffer,strlen(buffer));
					close(pc2p[1]);
					exit(0);
				break;
				default:{
					int w = scheduling_time - arr_time[process_index];
					awt+=w;
					sprintf(temp,"P-%d: At %d tick(s) new process comes (%d - %d), waited %d\n"
						,getpid(),scheduling_time,arr_time[process_index],burst_time[process_index],w);
					write_to_console(temp);
					//send burst time to child process
					close(pp2c[0]);
					char buffer[2];
					sprintf(buffer,"%d",burst_time[process_index]);
					write(pp2c[1],buffer, strlen(buffer));
					close(pp2c[1]);
					//wait for child to process
					wait(NULL);

					//receive the message
					close(pc2p[1]);
					int returned_time = 0;
					while(read(pc2p[0],&buffer[0],1)){
						returned_time*=10;
						returned_time+= buffer[0]-'0';
					}
					close(pc2p[0]);
					sprintf(temp,"P-%d: Handled the real running time of process %d: %d tick(s)\n"
						,getpid(),process_index,returned_time);
					write_to_console(temp);

					scheduling_time+=returned_time;
					atat += scheduling_time-arr_time[process_index];
				}
			}
			processed_num++;
			the_processed[process_index] = 1;
			printf("P-%d: get back CPU.\n",getpid());
		}else{
			//update time while waiting for process to arrive
			sleep(1);//one tick
			scheduling_time++;
			sprintf(temp,"P-%d: at %d tick(s) waiting for new process\n",getpid(),scheduling_time);
			write_to_console(temp);
		}

	}//end of while loop
	printf("\n\nReport:\nRunning time: %d\nAWT: %.2f tick(s)\nATAT: %.2f tick(s)\n"
		,scheduling_time,awt/(double)n,atat/(double)n);
	return 0;
}

