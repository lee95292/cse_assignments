#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>

int main()
{ 
  DIR *dp;
  struct dirent *dent;
  struct stat sbuf;
  char path[BUFSIZ];
  
  if((dp=opendir("hanbit")) ==NULL)
  { 
    perror("opendir:hanbit");
    exit(0);
  
    while((dent=readder(dp)))
    {
      if(dent->d_name[0]=='.')continue;
      else 
        break;
    }
    
    sprintf(path,"hanbit\s",
  }
