#include<stdio.h>
#include<utmpx.h>

int main()
{
  struct utmpx *utx;
  printf("--My who--\n");
 
  while((utx=getutxent()!=NULL))
  { 
    if(utx->ut_type!=USER_PROCESS)
    	continue;  
    printf("%s\t %s\t %s\n",utx->ut_user,utx->ut_line,utx->ut_host);
  }
  return 0;
}
