/**
 * Author : 201716422 이명규
 * Date : 2018.10.07
 * Description : fsoncat프로그램은,유닉스 시스템에서 파일에 관한 정보를 기술해주는 프로그램입니다.
 * */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
int main(int argc,char* argv[])
{
  struct stat buf;    //file의 정보를 저장할 stat buffer 구조체 변수를 선언합니다.
  int kind;           //file 의 type을 알아내기 위한 변수
  char* type;         //정수형 kind로부터 file의 type을 normal text로 저장할 변수
 
  if(argv[1]!=NULL)   // 파일이름 인자가 입력되었는지 체크하고, 입력되지 않았다면 경고와 함께 종료합니다
    stat(argv[1],&buf);
  else
  {
    printf("Usage: fsoncat file \n");
    exit(0);
  }
 
  kind = buf.st_mode & S_IFMT;
 
  switch(kind) //비트 And연산을 통해 알아낸 파일의 타입을 normal  text로 변환합니다.
  {
    case S_IFREG:
      type="Regular";
      break; 
    case S_IFIFO:
      type="FIFO";
      break; 
    case S_IFDIR:
       type="Directory";
       break; 
    case S_IFCHR:
       type="Character special";
       break;
     case S_IFBLK:
       type="Block special";
       break;
     case S_IFLNK:
	type="Symbolic Link";
	break;
     case S_IFSOCK:
       type="Socket";
       break;     
}
  //파일의 정보가 저장된 stat 구조체에서 정보들을 출력합니다.
  printf("File : %s\n",argv[1]);
  printf("Inode:%d\tType:%s\tMode:%d\tFlags:%d\n",
	(int)buf.st_ino,type, (unsigned int)buf.st_mode,(unsigned int)buf.st_uid);
  printf("User:%d\tGroup:%d\tSize:%d\n",(int)buf.st_uid,(int)buf.st_gid,(int)buf.st_size);
  printf("Links:%d\tBlockcount:%d\n\n",(int)buf.st_nlink,(int)buf.st_blocks);
    
        // time.h의 ctime 함수로 시간정보를 포멧팅해줍니다.   
  printf("ctime:%x - %s",(int)buf.st_ctime,ctime(&buf.st_ctime));  
  printf("atime:%x - %s",(int)buf.st_atime,ctime(&buf.st_atime));  
  printf("mtime:%x - %s",(int)buf.st_mtime,ctime(&buf.st_mtime)); 
  
  return 0;
}

