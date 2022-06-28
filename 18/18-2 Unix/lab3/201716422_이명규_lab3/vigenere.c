/*
 *Author 이명규
 *Date 2018.10.17
 *Description 원본 파일을 키값을 통해 암호화,복호화하는 프로그램
 * */
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define BUF_SIZE 256

void printEncrypt(FILE*, FILE*, char*);  // 암호화 함수
void printDecrypt(FILE*, FILE*, char*);  //복호화 함수

char buf[BUF_SIZE];
char* fOpt,*kOpt,*oOpt;

int main(int argc,char* argv[])
{
  int n;
  char cOrd='n';   //암호 또는 복호화 옵션문자
  FILE *rfp,*wfp;
  extern char* optarg;
  extern int optind,opterr,optopt;
  
  while(-1!=(n=getopt(argc,argv,"cd:f:k:o:"))) //옵션 처리
  {
    switch(n)
    {
      case 'c':
	if(cOrd=='d')
	{
	  printf("error:cannot encrypt and decrypt at the same time");  //c, d옵션은 동시에 사용 불가
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
      case 'f':
	if(optarg==NULL){
	  printf("Usage -f FileName\n");
	  exit(1);
	  }
	else
	{
	  fOpt=(char*)malloc(sizeof(optarg));
	  strcpy(fOpt,optarg);
	  printf("%s",fOpt);
	}
      break;
      case 'k': 
	if(optarg==NULL){
	  printf("Usage: -k KetName\n");
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

  if(fOpt==NULL)     //원본 파일 열기
  {
    perror("source file cannot open");
    exit(1);
  }else
    rfp=fopen(fOpt,"r");  
  
  if(oOpt==NULL)   // 암호화 저장 파일 열기
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

void printEncrypt(FILE* rfp, FILE* wfp,char* key) //암호화 기능 수행
{  
  int ch;
  int keyidx=0;
  while(!feof(rfp))
  {
    ch=fgetc(rfp);
    if(ch==EOF)       //EOF, 개행문자는 암호화하지 않는다
	break;
    if(ch=='\n'){
      fputc(ch,wfp);
    }else
    {
      if(keyidx>=strlen(key))keyidx=0;  //암호화 식
      ch=(ch+key[keyidx])%95;
      keyidx++;    
      fputc(ch+32,wfp);
    }
  }
}
 


void printDecrypt(FILE* rfp, FILE* wfp, char* key)
{
  int ch;
  int keyidx=0;
  while(!feof(rfp))
  {
    ch=fgetc(rfp);
    if(ch==EOF)     //개행문자는 복호화하지 않는다.
	break;
    if(ch=='\n'){
      fputc(ch,wfp);
    }else
    {
      if(keyidx>=strlen(key))keyidx=0;    //복호화 식
      //ch=ch>=key[keyidx]?(ch-key[keyidx])%95:(ch-key[keyidx]+95)%95;
      ch=ch-key[keyidx]%95-32;
      if(ch<32)
	ch+=95;
      keyidx++;
      fputc(ch,wfp);
    }
  }
}
