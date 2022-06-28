#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<fcntl.h>
#include<stdlib.h>
#include"kboard.h"

int main(int argc,char **argv){

        if(argc!=2){
                printf("invalid argument\n");
                return -1;
        }

        int clip = atoi(argv[1]);

        long res = kboard_copy(clip);
        printf("%ld\n",res);
        switch(res){
                case -1:
                        printf("Ringbuffer Full");
                        break;
                case -2:
                        printf("invalid argument");
                        break;
                case -3:
                        printf("test\n");
                        break;
        }


        return 0;


}
