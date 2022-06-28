/*
 *Author �̸��
 *Date 2018.11.07
 *Description ���� ������ ��/��ȣȭ ���ִ� ���α׷��Դϴ�. ���ϴ� ���� ���μ����� ���� ����ó������� �����մϴ�.
 * ���� �޸� ������ ���� ���η����� ���������� �����ϴ� ����� �̿��Ͽ� �ۼ��Ͽ����ϴ�.
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

void printEncrypt(int, char*);  //�ɼ��� c�ϰ�� ��ȣȭ, d�ϰ�� ��ȣȭ �۾��� �ϴ� �Լ��Դϴ�.

char cOrd='n';
char* fOpt,*kOpt,*oOpt;
int pcs=1;
int main(int argc,char* argv[])
{
  int n;
  int rfd;
  extern char* optarg;
  extern int optind,opterr,optopt;

  while(-1!=(n=getopt(argc,argv,"cdp:f:k:o:"))) //  �ɼ� ó��
  {
    switch(n)
    {
      case 'c':                                 //C, D �ɼ��� ó���մϴ�. ���ÿ� �� �ɼ��� ���� �� �����ϴ�.
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
       pcs= atoi(optarg);                                       //������ ���μ��� �� ����
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

  if((rfd=open(fOpt,O_RDONLY,0664))==-1)  //fileopen ����ó�� �� ���� ����
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

  fstat(rfd,&statb_r);  //f�ɼ����� ���� ������ statbuf�� �����մϴ�.
  fsize=(int)statb_r.st_size;

  addr_r=mmap(NULL,fsize,PROT_READ,MAP_SHARED,rfd,(off_t)0);    //f�ɼ����� ���� ���Ͽ� ���� �޸𸮸� �����մϴ�.

  while(runProcess<pcs){                //p�ɼ����� ���� ���ڸ�ŭ ���μ����� �����մϴ�.
    pid=wait(&stat);
    pids[runProcess]=fork();            //���μ��� ����

    if((wfd=open(oOpt,O_CREAT|O_RDWR,0664))==-1)        //��.��ȣȭ �����͸� ������ ������ �����մϴ�.
    {
       perror("writting file cannot open");
       exit(1);
     }
     fstat(wfd,&statb_w);               //o �ɼ����� ���� ������ statbuf�� �����մϴ�.
     addr_w=mmap(NULL,statb_w.st_size,PROT_WRITE,MAP_SHARED,wfd,(off_t)0);  //o �ɼ����� �޾� ������ ������ �޸� �����մϴ�//
     ftruncate(wfd,(off_t)fsize);       // wfd�� ������ ũ�⸦ read���ϰ� �����ݴϴ�.


    if(pids[runProcess]<0)              //���μ��� �������� ���� �� ���μ��� ���� : ���μ��� ���� ����
    {
      printf("process cannot start");
      return ;
    }else if(pids[runProcess]==0)       //���μ����� �����������
    {
       //printf("rp: %d ppid: %d,   pid: %d\n",runProcess,(int)getppid(),(int)getpid());
       for(i=fsize*runProcess/pcs;i<fsize*(runProcess+1)/pcs;i++)   //������ ���μ������� �Ҵ�� ��ġ���� ��.��ȣȭ�� �����մϴ�.
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


