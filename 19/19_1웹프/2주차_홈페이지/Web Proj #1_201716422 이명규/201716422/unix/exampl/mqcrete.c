#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>

struct mbuf
{
  long mtype;
  char mtext[80];
};
int main(void){
  key_t key;
  int msgid;
  struct mbuf mesg;
  key=ftok("keyfile",10);
	msgid=msgget(key,IPC_CREAT|0644);
	if(msgid==-1){
		perror("msgget");
		exit(1);
	}
	mesg.mtype=1;
	strcpy(mesg.mtext,"message Q test\n");
	if(msgsnd(msgid,(void*)&mesg,80,IPC_NOWAIT)==-1){
		perror("msgsnd");
		exit(2);
	}
}
