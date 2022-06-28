#include<linux/syscalls.h>
#include<linux/printk.h>
#include<linux/uaccess.h>
#include<linux/spinlock.h>
#define MAX_CLIP (5)

int ring[MAX_CLIP];
int ringHead=0,ringTail=0;
int count=0;
int initLockCheck=0;
spinlock_t lock;

long sys_kb_enqueue(int item){
	if(ringHead==ringTail&&count>=MAX_CLIP){
		//printk(KERN_ERR "error : now RingBuffer full");
		return -1;
	}else if(item<0){
		printk(KERN_ERR "error : invaild item");
		return -3;
	}

	ring[ringHead]=item;
	ringHead=(ringHead+1)%MAX_CLIP;
	if(count<MAX_CLIP)count++;
	//printk(KERN_DEBUG "enqueue %d H:%d T:%d",item,ringHead,ringTail);
	return 0;
}

long sys_kb_dequeue(int *user_buf){
	if(ringHead==ringTail&&count<=0){
		//printk(KERN_ERR "error : now RingBuffer empty");
		return -1;	
	}
	int pop = ring[ringTail];
	if(count>0)count--;

	ringTail=(ringTail+1)%MAX_CLIP;
	copy_to_user(user_buf,&pop,4);
		//printk(KERN_DEBUG "dequeue %d H:%d T:%d",pop,ringHead,ringTail);
	return 0;
}

long do_sys_kb_enqueue(int item){
	long res;
	if(initLockCheck==0){
		spin_lock_init(&lock);
		initLockCheck=1;
	}
	spin_lock(&lock);
	res= sys_kb_enqueue(item);
	spin_unlock(&lock);
	return res;
	
}

long do_sys_kb_dequeue(int *user_buf){
	long res;
	if(initLockCheck==0){
		spin_lock_init(&lock);
		initLockCheck=1;
	}
	spin_lock(&lock);
	res=sys_kb_dequeue(user_buf);
	spin_unlock(&lock);
	return res;
}
SYSCALL_DEFINE1(kb_enqueue,int,item){
	return do_sys_kb_enqueue(item);
}

SYSCALL_DEFINE1(kb_dequeue,int __user *,user_buf){
	return do_sys_kb_dequeue(user_buf);
}

