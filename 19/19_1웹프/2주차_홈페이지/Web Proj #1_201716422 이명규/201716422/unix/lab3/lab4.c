/*
 *Author 이명규
 *Date 2018.11.07
 *Description 원본 파일을 암/복호화 해주는 프로그램입니다. 원하는 수의 프로세스를 통해 병렬처리기능을 수행합니다.
 * 또한 메모리 매핑을 통해 프로레스간 파일정보를 공유하는 기술을 이용하여 작성하였습니다.
 */

#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/mman.h>
#define BUF_SIZE 256

void printEncrypt(int, char*);  //옵션이 c일경우 암호화, d일경우 복호화 작업을 하는 함수입니다.

char cOrd='n';
char* fOpt,*kOpt,*oOpt;
int pcs=1;
int main(int argc,char* argv[])
{
  int n;
  int rfd;
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

  if((rfd=open(fOpt,O_RDONLY,0664))==-1)  //fileopen 에러처리 및 파일 열기
  {
    perror("source file cannot open");
    exit(1);
  }
  
  if(cOrd=='n')
  {
    perror("Usage: use c or d option");
    exit(1);
  }else
    printEncrypt(rfd,kOpt);
   
  if(pcs<1)
  {
    perror("pcs more than 2");
    exit(1);
  }  
   close(rfd);
}

void printEncrypt(int rfd,char* key)
{  
 
  pid_t pids[5],pid;
  int runProcess=0,i,fsize,stat,wfd,ch,keyidx=0;
  caddr_t addr_r,addr_w;
  struct stat statb_r,statb_w;

  fstat(rfd,&statb_r);  //f옵션으로 읽은 파일의 statbuf를 저장합니다.
  fsize=(int)statb_r.st_size;
 
  addr_r=mmap(NULL,fsize,PROT_READ,MAP_SHARED,rfd,(off_t)0); 	//f옵션으로 읽은 파일에 대한 메모리를 매핑합니다.

  while(runProcess<pcs){		//p옵션으로 받은 숫자만큼 프로세스를 생성합니다.
    pid=wait(&stat);
    pids[runProcess]=fork();   		//프로세스 생성
   
    if((wfd=open(oOpt,O_CREAT|O_RDWR,0664))==-1)	//암.복호화 데이터를 저장할 파일을 생성합니다.
    {
       perror("writting file cannot open");
       exit(1);
     }
     fstat(wfd,&statb_w); 		//o 옵션으로 받은 파일의 statbuf를 저장합니다.
     addr_w=mmap(NULL,statb_w.st_size,PROT_WRITE,MAP_SHARED,wfd,(off_t)0);  //o 옵션으로 받아 생성한 파일을 메모리 매핑합니다//
     ftruncate(wfd,(off_t)fsize);	// wfd의 파일의 크기를 read파일과 맞춰줍니다.
      

    if(pids[runProcess]<0)		//프로세스 생성오류 검증 및 프로세스 실행 : 프로세스 생성 실패
    {
      printf("process cannot start");
      return ;
    }else if(pids[runProcess]==0) 	//프로세스가 생성됐을경우
    {  
       //printf("rp: %d ppid: %d,   pid: %d\n",runProcess,(int)getppid(),(int)getpid());
       for(i=fsize*runProcess/pcs;i<fsize*(runProcess+1)/pcs;i++)   //각각의 프로세스마다 할당된 위치에서 암.복호화를 실행합니다.
       {
         ch=addr_r[i];
         if(keyidx>=strlen(key))keyidx=0; 
    
         if(cOrd=='c')  
         {
           //encript
           if(ch=='\n'||ch==EOF)addr_w[i]=ch;
           else
             addr_w[i]=(ch+key[keyidx])%95+32;
         }else{
           //decript 
           if(ch=='\n'||ch==EOF)addr_w[i]=ch;
           else{
             ch=ch-key[keyidx]%95-32;
             if(ch<32)ch+=95;
             addr_w[i]=ch;
           }
         }
         keyidx++;
       }

       close(wfd);
       exit(0);
    }
    else
    {
	 //printf("ppid %d  pid %d\n------\n",getppid(),getpid());
    }
     runProcess++;
  }
}
 
 
