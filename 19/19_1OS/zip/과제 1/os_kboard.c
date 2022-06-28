#include<linux/syscalls.h>
#include<linux/printk.h>
#include<linux/uaccess.h>
#include<linux/spinlock.h>
#define MAX_CLIP (5)

int ring[MAX_CLIP];
int ringHead=0,ringTail=0;
int count=0;
int initLockCheck=0;

long sys_kb_enqueue(int item){
        if(count>=5){
                //printk(KERN_ERR "error : now RingBuffer full");
                return -1;
        }else if(item<0){
                //printk(KERN_ERR "error : invaild item");
                return -2;
        }

        ring[ringHead]=item;
        ringHead=(ringHead+1)%MAX_CLIP;

        count++;
        //printk(KERN_DEBUG "enqueue %d H:%d T:%d",item,ringHead,ringTail);
        return 0;
}

long sys_kb_dequeue(int *user_buf){
        if(count<=0){
                //printk(KERN_ERR "error : now RingBuffer empty");
                return -1;
        }
        int pop = ring[ringTail];
        count--;

        ringTail=(ringTail+1)%MAX_CLIP;

        if(copy_to_user(user_buf,&pop,1)){
                //printk(KERN_DEBUG "dequeue %d H:%d T:%d",pop,ringHead,ringTail);
        }
        return 0;
}

long do_sys_kb_enqueue(int item){
        return sys_kb_enqueue(item);

}

long do_sys_kb_dequeue(int *user_buf){
        return sys_kb_dequeue(user_buf);
}
SYSCALL_DEFINE1(kb_enqueue,int,item){
        return do_sys_kb_enqueue(item);
}

SYSCALL_DEFINE1(kb_dequeue,int __user *,user_buf){
        return do_sys_kb_dequeue(user_buf);
}

