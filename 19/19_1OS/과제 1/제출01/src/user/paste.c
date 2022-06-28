#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<fcntl.h>
#include"kboard.h"

int main(){
        int *pst;

        long res =kboard_paste(pst);

        switch(res){
                case -1:
                        printf("Ringbuffer Empty");
                        break;
        }


        printf("%d %d\n",*pst);

        return 0;
}
