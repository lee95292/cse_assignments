/*
 *Author �̸��
 *Date 2018.10.17
 *Description ���� ������ ��/��ȣȭ ���ִ� ���α׷��Դϴ�. ���ϴ� ���� ���μ����� ���� ����ó������� �����մϴ�.
 */

#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<wait.h>
#include<sys/stat.h>

#define BUF_SIZE 256

void printEncrypt(FILE*, FILE*, char*);  //��ȣȭ ��� ����
void printDecrypt(FILE*, FILE*, char*);  //��ȣȭ ��� ����

char buf[BUF_SIZE];
char* fOpt,*kOpt,*oOpt;

int main(int argc,char* argv[])
{
  int n;
  char cOrd='n';
  int pcs=0;
  FILE *rfp,*wfp;
  extern char* optarg;
  extern int optind,opterr,optopt;
  
  while(-1!=(n=getopt(argc,argv,"cdp:f:k:o:")))  �ɼ� ó��
  {
    switch(n)
    {
      case 'c':      				//C, D �ɼ��� ó���մϴ�. ���ÿ� �� �ɼ��� ���� �� �����ϴ�.
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
       pcs= atoi(optarg);  					//������ ���μ��� �� ����   
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
	  printf("Usage: -k KetName\n");  //������ ���� �� optarg ����
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

  if(fOpt==NULL)  //fileopen ����ó�� �� ���� ����
  {
    perror("source file cannot open");
    exit(1);
  }else
    rfp=fopen(fOpt,"r");  
  
  if(oOpt==NULL)
  {
    perror("writting file cannot open");
    exit(1);
  }else
     wfp=fopen(oOpt,"w"); 
  if(cOrd=='n')
  {
    perror("Usage: use c or d option");
    exit(1);
  }else if(cOrd=='c')
    printEncrypt(rfp,wfp,kOpt);
   else if(cOrd=='d')
    printDecrypt(rfp,wfp,kOpt);
   
   fclose(wfp);
   fclose(rfp);
}

void printEncrypt(FILE* rfp, FILE* wfp,char* key)
{  
 /* int ch;
  int keyidx=0;
  while(!feof(rfp))
  {
    ch=fgetc(rfp);
    if(ch==EOF)
	break;
    if(ch=='\n'){
      fputc(ch,wfp);
    }else
   `: {
      if(keyidx>=strlen(key))keyidx=0;
      ch=(ch+key[keyidx])%95;
      keyidx++;    
      printf("%d ",ch+32);  
      fputc(ch+32,wfp);
    }
  }*/
  pid_t pids[5],pid;
  int runProcess=0;
  int i,fsize;
  int start,end,ch;
  fseek(rfp,0,SEEK_END);
  fsize=ftell(rfp);    
  fseek(rfp,0,SEEK_SET);
    
  int unit=fsize%5==0?fsize/5:fsize/5+1;    	//���μ��� �ϳ��� ó���� ���� ��

  while(runProcess<5){
    i=runProcess;
    pids[runProcess]=fork();    		//���μ��� ����
    
    if(pids[runProcess]<0)			//���μ��� �������� ���� �� ���μ��� ����
    {
      printf("process cannot start");
      return ;
    }else if(pids[runProcess]==0)
    {
       while(ftell(rfp)<(i+1)*unit&&ftell(rfp)<=fsize)	//���μ����� �������� ��ȣȭ ó��
	{
	  ch=fgetc(rfp);
	  if(ch=='\n')
	    fputc(ch,wfp);
	  else if(ch==EOF)
	    break;
	  else 
	    fputc(ch,wfp);
	  
	}
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
