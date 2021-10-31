#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

struct task_struct *task;
struct data
{
    int pid;
    int ppid;
    int process;
    int state;
};
#define BUFFER_LENGTH 100000
struct data buff[BUFFER_LENGTH];

static int misc_open(struct inode *inode, struct file *file)
{
    pr_info("Banu: I have been awoken..\n");
    return 0;
}

static int misc_close(struct inode *inodep, struct file *filp)
{
    pr_info("Banu: Sleepy time..\n");
    return 0;
}

static ssize_t misc_write(struct file *file, const char __user *buf,
		       size_t len, loff_t *ppos)
{
    pr_info("Banu: Yummy - I just ate %d bytes..\n", len);
    return len; /* But we don't actually do anything with the data */
}

static ssize_t misc_read(struct file *file, char __user *out,
		       size_t len, loff_t *ppos)
{
    int cnt = 0;
    
    for_each_process(task)
    {
        cnt++;
        
        buff[cnt-1].pid = task->pid;
        buff[cnt-1].ppid = task->real_parent->pid;
        buff[cnt-1].process = task_cpu(task);
        buff[cnt-1].state = task->state;
        
        printk(KERN_INFO "PID=%d PPID=%d CPU=%d STATE=%ld", buff[cnt-1].pid, buff[cnt-1].ppid, buff[cnt-1].process, buff[cnt-1].state);
        
    }
    copy_to_user(out,buff,sizeof(buff));
    return cnt;
}

static const struct file_operations test_fops = {
    .owner			= THIS_MODULE,
    .write			= misc_write,
    .open			= misc_open,
    .read           = misc_read,
    .release		= misc_close,
    .llseek 		= no_llseek,
};

struct miscdevice test_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "process_list",
    .fops = &test_fops,
};

static int __init misc_init(void)
{
    int error;

    error = misc_register(&test_device);
    if (error) {
        pr_err("Banu: can't misc_register :(\n");
        return error;
    }

    pr_info("Banu: I'm in!!\n");
    return 0;
}

static void __exit misc_exit(void)
{
    misc_deregister(&test_device);
    pr_info("Banu: I'm out!!\n");
}

module_init(misc_init)
module_exit(misc_exit)

MODULE_DESCRIPTION("Process List");
MODULE_AUTHOR("Banu Prasanth Pulicharla");
MODULE_LICENSE("GPL");