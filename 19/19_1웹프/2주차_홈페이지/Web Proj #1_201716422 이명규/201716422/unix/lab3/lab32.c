/*
 *Author 이명규
 *Date 2018.10.17
 *Description 원본 파일을 암/복호화 해주는 프로그램입니다. 원하는 수의 프로세스를 통해 병렬처리기능을 수행합니다.
 */

#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#define BUF_SIZE 256

void printEncrypt(FILE*, FILE*, char*);  //암호화 기능 수행
void printDecrypt(FILE*, FILE*, char*);  //복호화 기능 수행

char buf[BUF_SIZE];
char* fOpt,*kOpt,*oOpt;
int pcs=1;
int main(int argc,char* argv[])
{
  int n;
  char cOrd='n';
  FILE *rfp,*wfp;
  extern char* optarg;
  extern int optind,opterr,optopt;
  
  while(-1!=(n=getopt(argc,argv,"cdp:f:k:o:")))	//  옵션 처리
  {
    switch(n)
    {
      case 'c':      				//C, D 옵션을 처리합니다. 동시에 두 옵션을 가질 수 없습니다.
	if(cOrd=='d')   
	{
	  printf("error:cannot encrypt and decrypt at the same time");
	  exit(1);
	}else
	  cOrd='c';
      break;
      case 'd':  
	if(cOrd=='c')
	{
	  printf("error:cannot encrypt and decrypt at the same time\n");
	  exit(1);
	}else
          cOrd='d';
      break;
      case 'p':
       pcs= atoi(optarg);  					//실행할 프로세스 수 지정   
      break; 
      case 'f':
	if(optarg==NULL){
	  printf("Usage -f FileName\n");
	  exit(1);
	  }
	else
	{
	  fOpt=(char*)malloc(sizeof(optarg));
	  strcpy(fOpt,optarg);
	}
      break;
      case 'k': 
	if(optarg==NULL){
	  printf("Usage: -k KetName\n");  //사용오류 에러 및 optarg 복사
	  exit(1); 
	}
	else
	{
	  kOpt=(char*)malloc(sizeof(optarg));
	  strcpy(kOpt,optarg);
	}
      break;
      case 'o':
	if(optarg==NULL){
	  printf("Usage: -o Output File\n");
    	  exit(1);
	}else
	{
	  oOpt=(char*)malloc(sizeof(optarg));
	  strcpy(oOpt,optarg);
	}
      break;
     }
  } 

  if(fOpt==NULL)  //fileopen 에러처리 및 파일 열기
  {
    perror("source file cannot open");
    exit(1);
  }else
    rfp=fopen(fOpt,"r");  
  
  if(cOrd=='n')
  {
    perror("Usage: use c or d option");
    exit(1);
  }else if(cOrd=='c')
    printEncrypt(rfp,wfp,kOpt);
   else if(cOrd=='d')
    printDecrypt(rfp,wfp,kOpt);
  if(pcs<1)
  {
    perror("pcs more than 2");
    exit(1);
  }  
   fclose(rfp);
}

void printEncrypt(FILE* rfp, FILE* wfp,char* key)
{  
 
  pid_t pids[5],pid;
  int runProcess=0;
  int i,fsize,stat;
  int start,end,ch,keyidx=0;
  fseek(rfp,0,SEEK_END);
  fsize=ftell(rfp);    
  fseek(rfp,0,SEEK_SET);
    
  int unit=fsize%5==0?fsize/5:fsize/5+1; 

  while(runProcess<pcs){
    i=runProcess;
       pid=wait(&stat);
    pids[runProcess]=fork();   		//프로세스 생성
   

  if(pids[runProcess]<0)			//프로세스 생성오류 검증 및 프로세스 싱행
    {
      printf("process cannot start");
      return ;
    }else if(pids[runProcess]==0)
    {  
       printf("rp: %d ppid: %d,   pid: %d\n",runProcess,(int)getppid(),(int)getpid());
       if(oOpt==NULL)
       {
         perror("writting file cannot open");
         exit(1);
       }else
         wfp=fopen(oOpt,"a");
       int pss=0;	//process writing index
      
       pss=fseek(rfp,fsize/pcs*runProcess,SEEK_SET);
       while(ftell(rfp)*pcs<fsize*(runProcess+1))	//프로세스의 실제적인 암호화 처리
	{
          printf("%d \n",ftell(rfp));
	  ch=fgetc(rfp);
	  if(ch=='\n')
	    fputc(ch,wfp);
	  else if(ch==EOF)
	    break;
	  else{
	    //descript algorithm
         }
	}
       fclose(wfp);
       exit(0);
    }
    else
    {
	 printf("ppid %d  pid %d\n------\n",getppid(),getpid());
    }
     runProcess++;
  }
}
 


void printDecrypt(FILE* rfp, FILE* wfp, char* key)
{
  int ch;
  int keyidx=0;
  while(!feof(rfp))
  {
    ch=fgetc(rfp);
    if(ch==EOF)
	break;
    if(ch=='\n'){
      fputc(ch,wfp);
    }else
    {
      if(keyidx>=strlen(key))keyidx=0;
      ch=ch-key[keyidx]%95-32;
      if(ch<32)
	ch+=95;
      keyidx++;
      printf("%d ",ch+32);
      fputc(ch,wfp);
    }
  }

}
