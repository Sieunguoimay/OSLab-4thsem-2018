#include<stdio.h>
#include<sys/ipc.h>//this header file is for the key_t and ftok() function
#include<sys/msg.h>//for msgget(), msgsnd(), msgrcv(),etc.

#define CLIENT_NUMBER 144
#define SERVER_NUMBER 127
typedef struct msg_buffer{
	long msg_type;
	char msg_text[100];//100 characters only =((
	//you can give many more things here..
} msg_buffer;

int main(){
	printf("Hello Message Queue from Msgq_server\n");

	//create a unique key (key_t) - i think key can be any number
	//but by using ftok() we generate a unique key for safer programming.
	//after this line is executed, from now on, the key is fixed for this 
	//pattern of pathname+proj_id. any other register on this pattern is
	//returned same key. the path name to the file must actually exist.
	//the key is depending on the current content of the file. 
	key_t key = ftok("msgq_client.c",101);
	if(key == -1){
		printf("Error: key is not created, check the pathname or proj_id\n");
		return 1;//don't run, it's not safe.
	}
	printf("I have a key: %d\n",key);



	//create a message queue.
	//there are 2 possible flags IPC_CREAT|IPC_EXCL, but what the hell is 0666???
	//again the id returned is an unpredicted number
	int msgid = msgget(key,0666|IPC_CREAT);
	if(msgid == -1){
		printf("Error: Message Queue is not created, check the provided key\n");
		return 1;//don't run, nothing to run
	}
	printf("Message Queue is created, id: %d\n",msgid);



	//initiate message
	msg_buffer message;
	//any number babe. who wants to read this message, use this number
	message.msg_type = CLIENT_NUMBER;
	printf("Enter a integer: ");
	int number;
	scanf("%d",&number);
	sprintf(message.msg_text,"%d",number);



	//send message	
	printf("Message patched (%ld-%s), ready to send.\n",message.msg_type, message.msg_text);
	if(msgsnd(msgid,&message,sizeof(msg_buffer)-sizeof(long),0)==-1){
		printf("Error: Something wrong with sending message\n");
		return 1;
	}	
	printf("Sent!\n");



	//receive message which is in binary format
	long type = SERVER_NUMBER;//the programmer VU, he told me that, this is the number that 
	//will send me the message I need.
	printf("Waiting for a message of the type: %ld\n", type);
	int n = msgrcv(msgid,&message,sizeof(msg_buffer)-sizeof(long),type,0);
	if(n==-1){
		printf("Error: Something wrong with receiving message\n");
		return 1;
	}
	printf("Got a message (%ld - %s) (size: %d)\n",message.msg_type, message.msg_text,n);;




	//delete message queue, after this 	
	//what if the msgq is not deleted???
	if(msgctl(msgid, IPC_RMID, NULL)==-1){
		printf("Error: Cannot delete the message queue, check msgid\n");
		return 1;
	}
	printf("Msgq is deleted \n");
	return 0;
}
