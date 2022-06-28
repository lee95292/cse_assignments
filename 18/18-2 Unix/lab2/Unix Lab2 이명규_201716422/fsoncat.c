/**
 * Author : 201716422 �̸��
 * Date : 2018.10.07
 * Description : fsoncat���α׷���,���н� �ý��ۿ��� ���Ͽ� ���� ������ ������ִ� ���α׷��Դϴ�.
 * */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
int main(int argc,char* argv[])
{
  struct stat buf;    //file�� ������ ������ stat buffer ����ü ������ �����մϴ�.
  int kind;           //file �� type�� �˾Ƴ��� ���� ����
  char* type;         //������ kind�κ��� file�� type�� normal text�� ������ ����
 
  if(argv[1]!=NULL)   // �����̸� ���ڰ� �ԷµǾ����� üũ�ϰ�, �Էµ��� �ʾҴٸ� ���� �Բ� �����մϴ�
    stat(argv[1],&buf);
  else
  {
    printf("Usage: fsoncat file \n");
    exit(0);
  }
 
  kind = buf.st_mode & S_IFMT;
 
  switch(kind) //��Ʈ And������ ���� �˾Ƴ� ������ Ÿ���� normal  text�� ��ȯ�մϴ�.
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
  //������ ������ ����� stat ����ü���� �������� ����մϴ�.
  printf("File : %s\n",argv[1]);
  printf("Inode:%d\tType:%s\tMode:%d\tFlags:%d\n",
	(int)buf.st_ino,type, (unsigned int)buf.st_mode,(unsigned int)buf.st_uid);
  printf("User:%d\tGroup:%d\tSize:%d\n",(int)buf.st_uid,(int)buf.st_gid,(int)buf.st_size);
  printf("Links:%d\tBlockcount:%d\n\n",(int)buf.st_nlink,(int)buf.st_blocks);
    
        // time.h�� ctime �Լ��� �ð������� ���������ݴϴ�.   
  printf("ctime:%x - %s",(int)buf.st_ctime,ctime(&buf.st_ctime));  //������ ���� �ð�
  printf("atime:%x - %s",(int)buf.st_atime,ctime(&buf.st_atime));  //������ ������ �ð�
  printf("mtime:%x - %s",(int)buf.st_mtime,ctime(&buf.st_mtime));  // ������ ���� �ð�
  
  return 0;
}

