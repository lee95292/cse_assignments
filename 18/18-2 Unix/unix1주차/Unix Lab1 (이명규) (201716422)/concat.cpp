/*
 * Author �̸��
 * Date 2018_09_16
 * Explanation cat ��ɾ��� �Ϻ� ����� �����ϴ� concat��ɾ �ۼ��մϴ�.
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#define BUF_SIZE 64

void ViewOption(FILE*, int);  //Viewoption�� ���ڷ� �־�, �ش� �ɼ��� ���ϴ� �Լ�
void CreateOption(FILE*,FILE*); // Create Option(o)�� ���� ��� �����ϴ� �Լ�
char *lOpt,*oOpt; // l�ɼ��� �Ķ����, o�ɼ��� �Ķ����

int main(int argc,char* argv[])
{

  extern char* optarg;
  extern int optind,opterr,optopt;
  FILE *rfp,*wfp;
  int n;
  int viewOpt=0,creatOpt=0; 
  char buf[BUF_SIZE];
 
 while(-1!=(n=getopt(argc,argv,"o:l:nsh")))  //getopt�� ����Ͽ� �ɼ��� ó���մϴ�
  {
    switch(n){
	case 'h':		//help page option
	  printf("Usage: concat [option..][file..]\n");
  	  printf("The available options are following:\n"); 	  
	  printf("  -n : display line numbers\n");
	  printf("  -s : surpress repeated empty output linews\n");
	  printf("  -o fileName : create output file named fileName\n");
  	  printf("  -l N : set page length as N line\n");
	  printf("  -h : display a help file\n");
	  exit(0);
	case 'l': 		//(viewOpt 001) limited format option	
	  if(optarg==NULL)
	    printf("Usage : -l N(Number) ");
	  else
	    lOpt=malloc(sizeof(optarg)); 
	    memcpy(lOpt,optarg,sizeof(optarg));
    	   viewOpt+=1;
	  break;
	case 'n':		//(viewOpt 010) line number express option
	  viewOpt+=2;
	  break;	
	case 's':		//(viewOpt 100) supress repeated newline	
	  viewOpt+=4;
	  break;
	case 'o':		//open new file
	  oOpt=malloc(sizeof(optarg));
	  if(optarg==NULL)
	    printf("Usage : -o F(New filename)");
	  else
	    memcpy(oOpt,optarg,sizeof(optarg));
	  creatOpt=1;
	  break;
    }
  }
  rfp=fopen(argv[argc-1],"r");
  
   if(creatOpt) //O�ɼ��� ����� ��¿ɼ��� ó���մϴ�.
  { 
    wfp=fopen(oOpt,"w");   
    if(wfp==NULL)
    {
      perror("fopen:cannot");
      exit(1);   
    } 
    rewind(rfp); 
    CreateOption(wfp,rfp);
  }
 
  if(argc>1) //������ �о�, ������ݴϴ�.
  {     
    if(rfp==NULL)
    {
      perror("fopen:cannot");
      exit(1);   
    } 
    ViewOption(rfp,viewOpt);  
  } 

  fclose(rfp);
  fclose(wfp);
	
  return 0;
}

void ViewOption(FILE* rfp, int opt) //processing Viewoption
{
  char buf[BUF_SIZE];

  int n=0,l=0,s=0,lineP;

  int lineCnt=0,lineNum=1;

  if(opt>=4){  //ViewOption setting
    s=1;
    opt-=4;
  }
  if(opt>=2){
   n=1;
   opt-=2;
  }
  if(opt>=1)
   l=1;

  int sflag=0;
  if(lOpt!=NULL)lineP=atoi(lOpt);  
  while(fgets(buf,BUF_SIZE-1,rfp)!=NULL)
  {
    if(s)								//S opt
    {
	if(0==strcmp(buf,"\n")&&sflag==1)
          continue;
	else if(0==strcmp(buf,"\n")&&sflag==0)
  	  sflag=1;
	else 
	  sflag=0;
    }    
   if(n)
      printf("%d  ",lineNum++);

    printf("%s",buf);  // print buffer(file)
   
    lineCnt++; 
    if(lineCnt==lineP)
    {  
      lineCnt=0;
      if(getc(stdin)=='\n')  //Press 'Return' (Enter Button) to next page
	continue;
      else lineCnt=lineP+1;  
    }
  } 
}

void CreateOption(FILE* wfp,FILE *rfp) //execute O option
{
  char buf[BUF_SIZE];

  while(fgets(buf,BUF_SIZE,rfp)!=NULL)
   fputs(buf,wfp);  
}

