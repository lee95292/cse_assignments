#include <linux/slab.h>
#include <linux/module.h>       /* for module programming */
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>        /* for copy_from_user */
#include <linux/semaphore.h>
#include <linux/list.h>
#include <linux/spinlock.h>

#define MAX_LEN (10)             // max of character length : integer 2^31-1  , 
#define RING_SIZE (5)
///     ring implement         ///
int ringBuffer[RING_SIZE];
short ringHead;
short ringTail;
short count;
///////////////////////////////////

static inline void my_sema_init(struct semaphore *sem, int val)
{
	static struct lock_class_key __key;
	*sem = (struct semaphore) __SEMAPHORE_INITIALIZER(*sem, val);
	lockdep_init_map(&sem->lock.dep_map, "semaphore->lock", &__key, 0);
}
///     Syncroniz  & test ///
extern struct semaphore mutex;
extern struct semaphore wrt;
extern struct semaphore reads;
        
int rc,wc,rwc,wwc;
DEFINE_SEMAPHORE(mutex);
DEFINE_SEMAPHORE(wrt);
DEFINE_SEMAPHORE(reads);
int readerCall;
int writerCall;
///////////////////////////

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Youngil, Moon <jake9999@.com>");
MODULE_DESCRIPTION("A sample driver");
MODULE_LICENSE("Dual BSD/GPL");
/*--------------------------------------------------------*/
/* 1) Generate sample data    & initialize                */
/*--------------------------------------------------------*/

static void init_data(void){
        int i;
        ringHead=0;
        ringTail=0;
        count=0;
        for(i=0;i<RING_SIZE;i++){
                ringBuffer[i]=0;
        }
        
        rc=0;wc=0;rwc=0;wwc=0;
        readerCall=0;
        writerCall=0;
        my_sema_init(&wrt,0);
        my_sema_init(&reads,0);
}

/*--------------------------------------------------------*/
/* 2) proc operations part                                */
/*--------------------------------------------------------*/

static int kboard_simple_show(struct seq_file *s, void *unused)
{ 
        return 0;
}

static int kboard_proc_open(struct inode *inode, struct file *file)
{
        return single_open(file, kboard_simple_show, NULL);
}

/*--------------------------------------------------------*/
/* 2-1) proc operations : writer                          */
/*--------------------------------------------------------*/

static int kboard_enqueue(int clip){                 //main logic for ringbuffer_write
        if(ringHead==ringTail&&count==RING_SIZE){
                return -1;
        }else if(clip<0){
                return -2;
        }
        ringBuffer[ringHead] = clip;
        ringHead = (ringHead+1)%RING_SIZE;
        count++;
        //printk(KERN_INFO "HEAD: %d, TAIL %d, COUTNT:%d, CLIP:%d",ringHead,ringTail,count,clip);
        //printk(KERN_INFO " ");

        return 0;
}

static ssize_t do_kboard_enqueue(struct file *write, const char __user* usr, size_t len, loff_t *data){
        unsigned long int bufSize = len;
        char tmpBuf[MAX_LEN];
        int clip;
        int res;
        int i;

        writerCall++;

        if(MAX_LEN<bufSize){
                bufSize=MAX_LEN;
                //printk(KERN_INFO "INVALID DATA");
                return -2;           
        }
        if(copy_from_user(tmpBuf,usr,bufSize)){
                //printk(KERN_INFO "copy failed");
                return -3;
        }
        
        clip = simple_strtol(tmpBuf,NULL,10);            
        
        down(&mutex);
        if(rc>0||wc>0||rwc>0||wwc>0){
                wwc++;
                up(&mutex);
                down(&wrt);
                down(&mutex);
                wwc--;
        }
        wc++;
        up(&mutex);
        res = kboard_enqueue(clip);
        down(&mutex);
        wc--;
        if(rwc>0){
                for(i=0;i<rwc;i++){
                        up(&reads);
                }
        }else if(wwc>0){
                up(&wrt);
        }
        up(&mutex);

        if(res==-1){
                //printk(KERN_INFO "now ring buffer full");
                return -1;
        }else if(res==-2){
                //printk(KERN_INFO "invalid data");
                return -2;
        }
        return res;
        
}



static int kboard_dequeue(void){                   //main logic for ringbuffer_read
        int pop;
        if(ringHead==ringTail&&count==0){
                return -1;
        }

        pop=ringBuffer[ringTail];
        ringTail =(ringTail+1)%RING_SIZE;
        count--;
        //printk(KERN_INFO "HEAD: %d, TAIL %d, COUTNT:%d POP:%d",ringHead,ringTail,count,pop);
        //printk(KERN_INFO " ");
        return pop;
}

static  ssize_t do_kboard_dequeue(struct file *read, char __user *usr, size_t size, loff_t *data){
        char tmpBuf[MAX_LEN];
        unsigned long int bufSize;
        int res;
        int i;

        writerCall++;

        down(&mutex);
        if(rc>0||wc>0||rwc>0||wwc>0){
                wwc++;
                up(&mutex);
                down(&wrt);
                down(&mutex);
                wwc--;
        }
        wc++;
        up(&mutex);
        res= kboard_dequeue();
        down(&mutex);
        wc--;
        if(rwc>0){
                for(i=0;i<rwc;i++){
                        up(&reads);
                }
        }else if(wwc>0){
                up(&wrt);
        }
        up(&mutex);
        if(res==-1){
                //printk(KERN_INFO "now ring buffer empty");
        }

        sprintf(tmpBuf,"%d",res);               
        bufSize=sizeof(tmpBuf);
        if(copy_to_user(usr,tmpBuf,bufSize)){         
                //printk(KERN_INFO "ERR: COPY TO USER");
                return -EFAULT;
        }

        return 0;
}

/*--------------------------------------------------------*/
/* 2-2) proc operations : reader                          */
/*--------------------------------------------------------*/
static int kboard_read(void){
        int res;
        
        if(count==0&&ringHead==ringTail){
                return -1;
        }
        res=ringBuffer[ringHead];
        return res;
        //origin return value  = ring[(ringHead + rand(0,count-1))%RING_SIZE];
}

static ssize_t do_kboard_read(struct file *read, char __user *usr, size_t size, loff_t *data){
        char tmpBuf[MAX_LEN];
        unsigned long int bufSize;
        int res;
        
        readerCall++;

        down(&mutex);
        if(wwc>0||wc>0){
                rwc++;
                up(&mutex);
                down(&reads);
                down(&mutex);
                rwc--;
        }
        rc++;
        up(&mutex);
        res = kboard_read();
        down(&mutex);
        rc--;
        if(rc==0&&wwc>0)up(&wrt);
        up(&mutex);

        if(res==-1){
                //printk(KERN_INFO "now ring buffer empty");
                return 0;
        }
        sprintf(tmpBuf,"%d",res);
        bufSize=sizeof(tmpBuf);
        if(copy_to_user(usr,tmpBuf,bufSize)){
                //printk(KERN_INFO "ERR: COPY TO USER");
                return -EFAULT;
        }
        return 0;
}

/*--------------------------------------------------------*/
/* 2-3) proc operations : file_ops                        */
/*--------------------------------------------------------*/
static const struct file_operations foo_proc_ops = {
        .owner          = THIS_MODULE,
        .open           = kboard_proc_open,
        .read           = seq_read,
        .llseek         = seq_lseek,
        .release        = seq_release,
};

static const struct file_operations dequeue_proc_ops={
        .owner          = THIS_MODULE,
        .open           = kboard_proc_open,
        .read           = do_kboard_dequeue,
};

static const struct file_operations enqueue_proc_ops={
        .owner          = THIS_MODULE,
        .open           = kboard_proc_open,
        .write          = do_kboard_enqueue,
};

static const struct file_operations read_proc_ops={
        .owner          = THIS_MODULE,
        .open           = kboard_proc_open,
        .read           = do_kboard_read,
};

/*--------------------------------------------------------*/
/* 3) TEST perform                                           */
/*--------------------------------------------------------*/


static ssize_t test_kboard_read(struct file *read, char __user *usr, size_t size, loff_t *data){
        char tmpBuf[30];
        sprintf(tmpBuf,"reader_%d, writer_%d",readerCall,writerCall);
        
        if(copy_to_user(usr,tmpBuf,sizeof(tmpBuf))){
                //printk(KERN_DEBUG "test_kboard_read err: copy to user");
                return -EFAULT;
        }
        
        printk(KERN_DEBUG "reader_%d, writer_%d",readerCall,writerCall);
        printk(KERN_DEBUG "");
        
        readerCall=0;
        writerCall=0;
        return 0;
}
static const struct file_operations test_proc_ops={
        .owner          = THIS_MODULE,
        .open           = kboard_proc_open,
        .read           = test_kboard_read,
};
/*--------------------------------------------------------*/
/* 4) proc interface part  (/proc/foo-dir/foo)            */
/*--------------------------------------------------------*/

#define FOO_DIR "kboard"
#define DEQUEUE "dequeue"
#define ENQUEUE "enqueue"
#define RD_FILE "reader"

#define TEST_FILE "testperform"

static struct proc_dir_entry *kboard_proc_dir = NULL;
static struct proc_dir_entry *dequeue_proc_file = NULL;
static struct proc_dir_entry *equeue_proc_file=NULL;
static struct proc_dir_entry *read_proc_file =NULL;

static struct proc_dir_entry *test_proc_file =NULL; 

int foo_proc_init(void)
{
        ////foo-dir////
        kboard_proc_dir = proc_mkdir(FOO_DIR, NULL);
        if (kboard_proc_dir == NULL)
        {
                printk("Unable to create /proc/%s\n", FOO_DIR);
                return -1;
        }

        
        ///file-create///

        dequeue_proc_file = proc_create(DEQUEUE, 0, kboard_proc_dir, &dequeue_proc_ops); /* S_IRUGO */ 
        equeue_proc_file = proc_create(ENQUEUE,0,kboard_proc_dir,&enqueue_proc_ops);
        read_proc_file = proc_create(RD_FILE,0,kboard_proc_dir,&read_proc_ops);
        test_proc_file = proc_create(TEST_FILE,0,kboard_proc_dir,&test_proc_ops);

        if (dequeue_proc_file == NULL)
        {
                printk("Unable to create /proc/%s/%s\n", FOO_DIR, DEQUEUE);
                remove_proc_entry(FOO_DIR, NULL);
                return -1;
        }

        if(equeue_proc_file==NULL)
        {
                printk("Unable to create /proc/%s/%s\n",FOO_DIR,ENQUEUE);
                remove_proc_entry(FOO_DIR,NULL);
                return -1;
        }

        if(read_proc_file==NULL)
        {
                printk("Unable to create /proc/%s/%s\n",FOO_DIR,RD_FILE);
                remove_proc_entry(FOO_DIR,NULL);
                return -1;
        }

        if(test_proc_file==NULL){
                printk("Unable to create /proc/%s/%s\n",FOO_DIR,TEST_FILE);
                remove_proc_entry(FOO_DIR,NULL);
                return -1;        
        }

        
        printk(KERN_INFO "Created /proc/%s/%s /proc/%s/%s\n", FOO_DIR, DEQUEUE,FOO_DIR,ENQUEUE);
        return 0;
}

void foo_proc_exit(void)
{
        /* remove directory and file from procfs */
        remove_proc_subtree(FOO_DIR, NULL);

        /* remove proc_dir_entry instance */
        proc_remove(dequeue_proc_file);
        proc_remove(equeue_proc_file);
        proc_remove(read_proc_file);
        proc_remove(test_proc_file);
        proc_remove(kboard_proc_dir);

        printk(KERN_INFO "Removed /proc/%s/%s\n", FOO_DIR, DEQUEUE);
}

/*--------------------------------------------------------*/
/* 2) Module part                                         */
/*--------------------------------------------------------*/

static int __init kboard_init(void)
{
        init_data();

        return foo_proc_init();
}

static void __exit kboard_exit(void)
{
        //remove_sample_data();
        foo_proc_exit();

        return;
}

module_init(kboard_init);
module_exit(kboard_exit);
