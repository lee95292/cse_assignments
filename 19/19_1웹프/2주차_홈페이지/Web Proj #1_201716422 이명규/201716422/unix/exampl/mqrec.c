#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>

struct mbuf
{
  long mtye;
  char mtext[80];
};
int main(void){
  key_t key;
  int msgid,len;
	struct mbuf inmsg;
	key=ftok("keyfile",10);
	if((msgid=msgget(key,0))<0)
	{
		perror("msgget");
		exit(1);
	}
	len=msgrcv(msgid, &inmsg, 80, 0,0);
	printf("RCV message: %s lengg:%d\n",inmsg.mtext,len);
	return 0;
}
