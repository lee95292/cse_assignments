#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<fcntl.h>
#include"kboard.h"

int main(){
        int a;
        int *pst=&a;
        int cnt=1;
        long res=-1;
        while(1){
                res=kboard_paste(pst);
                if(res==0&&cnt!=*pst){
                        printf("Validation Fault! current %d mustbe %d\n",*pst,cnt);
                        return -1;
                }
                if(res==0)cnt++;

        }

        return 0;
}
