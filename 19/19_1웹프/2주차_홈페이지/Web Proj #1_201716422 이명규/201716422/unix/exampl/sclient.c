#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SOCKET	"testsocket"
int main(void) {
  char buf[256];
  int sd, len;
  struct sockaddr_un ser;
  if((sd=socket(AF_UNIX, SOCK_STREAM, 0))==-1) {
    perror("socket");
    exit(1);
  }
  memset((char *)&ser, '\0', sizeof(ser));
  ser.sun_family = AF_UNIX;
  strcpy(ser.sun_path, SOCKET);
  len = sizeof(ser.sun_family)+strlen(ser.sun_path);
  if(connect(sd, (struct sockaddr *)&ser, len) <0) {
    perror("connect");
    exit(2);
  }
  strcpy(buf, "Unix domain socket test");
  if(send(sd, buf, sizeof(buf),0)==-1) {
    perror("send");
    exit(3);
  }
  close(sd);
  return 0;
}
