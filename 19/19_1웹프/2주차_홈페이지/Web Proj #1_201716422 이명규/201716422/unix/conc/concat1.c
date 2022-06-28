/*
 * Author 이명규
 * Date 2018_09_16
 * Explanation cat 명령어의 일부 기능을 수행하는 concat명령어를 작성합니다.
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#define BUF_SIZE 64

void ViewOption(FILE*, int);  //Viewoption을 인자로 주어, 해당 옵션을 실하는 함수
void CreateOption(FILE*,FILE*); // Create Option(o)에 대한 명령 수행하는 함수
char *lOpt,*oOpt; // l옵션의 파라미터, o옵션의 파라미터

int main(int argc,char* argv[])
{

  extern char* optarg;
  extern int optind,opterr,optopt;
  FILE *rfp,*wfp;
  int n;
  int viewOpt=0,creatOpt=0; 
  char buf[BUF_SIZE];
 
 while(-1!=(n=getopt(argc,argv,"o:l:nsh")))  //getopt를 사용하여 옵션을 처리합니다
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
  
   if(creatOpt) //O옵션을 사용해 출력옵션을 처리합니다.
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
 
  if(argc>1) //파일을 읽어, 출력해줍니다.
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
  if(lOpt!=NULL)lineP=atoi(lOpt);   // char* 형태의 lOpt를 숫자로 바꿔줍니다.
  while(fgets(buf,BUF_SIZE-1,rfp)!=NULL)
  {
    if(s)
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
      if(getc(stdin)=='\n')  //Press 'Return' to next page
	continue;
      else lineCnt=lineP+1;  
    }
  } 
}

void CreateOption(FILE* wfp,FILE *rfp) //-o 옵션을 처리합니다.
{
  char buf[BUF_SIZE];

  while(fgets(buf,BUF_SIZE,rfp)!=NULL)
   fputs(buf,wfp);  
}
