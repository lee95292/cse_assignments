#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<fcntl.h>
#include<stdlib.h>
#include"kboard.h"

int main(){

        int clip=1;
        while(1){
                long res = kboard_copy(clip);

                if(res==0){
                        printf("copy %d\n",clip);
                        clip++;

                }
        }

}
