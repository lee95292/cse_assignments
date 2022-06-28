/*
 * Author 이명규
 * Date
 * Explanation
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#define BUF_SIZE 1024
int main(int argc,char* argv[])
{
  int c,n,wfd,rfd;
  extern char* optarg;
  extern int optind,opterr,optopt;
  char buf[BUF_SIZE];
 
 while(-1!=(n=getopt(argc,argv,"o:l:nsh")))
  {
    switch(n)
    {
	case 'l':
	  printf("l option\n");
	  break;
	case 'h':
	  printf("h option");
	  break;
	default:
	 printf("ind:%d\n",optind);
    }
  }

  rfd=open(argv[argc-1],O_RDONLY);
   while((c=read(rfd,buf,BUF_SIZE-1))>0);
     printf("%s",buf); 
   printf("\n\nrfd::%d\n\n",rfd);
  close(rfd);
  return 0;

}

