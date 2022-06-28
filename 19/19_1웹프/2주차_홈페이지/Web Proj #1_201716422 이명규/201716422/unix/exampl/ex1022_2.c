#include<stdio.h>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char*argv[])
{
  int fd;
  caddr_t addr;
  struct stat statbuf;
  char* tmp;
  pid_t pid;
	int i;
  if(argc !=2 )
  {
    fprintf(stderr,"Usage:%s filename",argv[0]);
    exit(1);
  }
  if(stat(argv[1],&statbuf)==-1)
  {
    perror("stat");
    exit(1);
  }
  if((fd=open(argv[1],O_RDWR))==-1)
  {
    perror("open");
    exit(1);
  }
 
  addr=mmap(NULL,statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,(off_t)0);
  switch(pid=fork())
	{
		case 0:
			perror("fork");
			exit(1);
			break;
		case 1:
			for(i=0;addr[i]!=statbuf.st_size;i++)
			{
				addr[i]='c';	
			}
		break;
	
	}
  if(addr==MAP_FAILED)
  {
    perror("mmap");
    exit(1);
  }
  close(fd);
  printf("%s",addr);

  tmp=&addr[1];
  strcpy(addr,"hello");
  //addr[0]='x';
  printf("-------------------\n"); 
  printf("%s",addr);
  return 0;
}
