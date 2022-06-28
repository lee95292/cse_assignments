#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define START_PORT 13000
#define END_PORT   13003
int main()
{
 int i;
 struct sockaddr_in sin[30000];
 int sd[30000];
 for(i=START_PORT;i<END_PORT;i++)
 {
  if((sd[i]=socket(AF_INET,SOCK_STREAM,0)) == -1)
  {
    perror("socket");
  }else printf("sock fuck %d \n",i);
 }
 for(i=START_PORT;i<END_PORT;i++)
 {
  sin[i].sin_family=AF_INET;
  sin[i].sin_port=htons(i);
  sin[i].sin_addr.s_addr=htonl(INADDR_ANY);
  if(bind(sd[i],(struct sockaddr*)&sin[i],sizeof(sin[i])))
  {
    perror("bind");
  }else printf("fuck bind %d \n",i);
  
  if(fork()==0)
  {
    if(listen(sd[i],END_PORT-START_PORT))
    {
      perror("listen");
    }else printf("listen fuck %d \n",i);
  }
}
 
}
