#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SOCKET "testsocket"
int main(void) {
  char buf[256];
  struct sockaddr_un ser, cli;
  int sd, nsd, len, clen;
  if((sd=socket(AF_UNIX, SOCK_STREAM, 0))==-1) {
    perror("socket");
    exit(1);
  }
  memset((char *)&ser, 0, sizeof(struct sockaddr_un));
  ser.sun_family =AF_UNIX;
  strcpy(ser.sun_path, SOCKET);
  len = sizeof(ser.sun_family)+strlen(ser.sun_path);
  if(bind(sd, (struct sockaddr *)&ser, len)) {
    perror("bind");
    exit(2);
  }
  if(listen(sd, 5) < 0) {
    perror("listen");
    exit(3);
  }
  printf("Waiting...\n");
  if((nsd = accept(sd, (struct sockaddr *)&cli, &clen))==-1){
    perror("accept");
    exit(4);
  }
  if(recv(nsd, buf, sizeof(buf), 0)==-1) {
    perror("receiv");
    exit(5);
  }
  printf("Received message: %s\n", buf);
  close(nsd);
  close(sd);
  return 0;
}

