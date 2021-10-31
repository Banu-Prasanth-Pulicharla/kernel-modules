#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

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
    char buf[20];
    sprintf(buf,"Hello World!");
    copy_to_user(out,buf,strlen(buf)+1);
    return strlen(buf)+1;
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
    .name = "misc_char_dd_banu",
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

MODULE_DESCRIPTION("Test Misc Driver");
MODULE_AUTHOR("Banu Prasanth Pulicharla");
MODULE_LICENSE("GPL");