#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>


// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omar Adel Shalaan");
MODULE_DESCRIPTION("register_chrdev && unregister_chrdev");


int major = 0;
module_param(major, int, 0);
MODULE_PARM_DESC(major, "An integer parameter that will be major device");


int driver_open (struct inode *driver_inode, struct file * driver_file)
{
    printk("Driver Open\n");
    return 0;
}

static struct file_operations my_device_fops = {
    // Define file operation functions such as open, read, write, etc.
    .open = driver_open,
    .owner = THIS_MODULE
};


static int __init Add_Device_init(void)
{
    //static inline int register_chrdev(unsigned int major, const char *name, const struct file_operations *fops)
    int retval = register_chrdev(major,"Shalaan_dev", &my_device_fops);
    if(retval == 0)
        printk("Shalaan_dev created Major:%d\n",major);
    else
    {
        printk("Shalaan_dev Not created\n");
        return -1;
    }
    return 0;
}

static void __exit Add_Device_exit(void)
{
    // static inline void unregister_chrdev(unsigned int major, const char *name)
    unregister_chrdev(major , "Shalaan_dev");
    printk("Bye Add Device exit\n");
}

module_init(Add_Device_init);
module_exit(Add_Device_exit);
