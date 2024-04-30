#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>


// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omar Adel Shalaan");
MODULE_DESCRIPTION("alloc_chrdev_region");



int driver_open (struct inode *driver_inode, struct file * driver_file)
{
    printk("alloc_chrdev_region Driver Open\n");
    return 0;
}

static struct file_operations my_device_fops = {
    // Define file operation functions such as open, read, write, etc.
    .open = driver_open,
    .owner = THIS_MODULE
};

dev_t dev;
static int __init Add_Device_init(void)
{
    int retval = alloc_chrdev_region(&dev, 0, 0, "alloc_shalaan_dev");
    if(retval == 0)
        printk("alloc_chrdev_region created Major:%d Minor: %d\n", MAJOR(dev),MINOR(dev));
    else
    {
        printk("alloc_chrdev_region Not created\n");
        return -1;
    }
    return 0;
}

static void __exit Add_Device_exit(void)
{
    //extern void unregister_chrdev_region(dev_t, unsigned);
    unregister_chrdev_region(dev,0);
    printk("Bye alloc_chrdev_region Device exit\n");
}

module_init(Add_Device_init);
module_exit(Add_Device_exit);