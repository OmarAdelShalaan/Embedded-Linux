#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>
#include <linux/cdev.h>

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omar Adel Shalaan");
MODULE_DESCRIPTION("cdev_init_cdev_add");



int driver_open (struct inode *driver_inode, struct file * driver_file)
{
    printk("cdev_init_cdev_add Driver Open\n");
    return 0;
}

static struct file_operations my_device_fops = {
    // Define file operation functions such as open, read, write, etc.
    .open = driver_open,
    .owner = THIS_MODULE
};
struct cdev st_Cdevive;
dev_t dev;
struct class *mydevice_class;
struct device *mydevice;
static int __init Add_Device_init(void)
{
    // allocate device number
    int retval = alloc_chrdev_region(&dev, 0, 0, "alloc_shalaan_dev");
    if(retval == 0)
        printk("alloc_chrdev_region created Major:%d Minor: %d\n", MAJOR(dev),MINOR(dev));
    else
    {
        printk("alloc_chrdev_region Not created\n");
        return -1;
    }
    // define driver character 
    //void cdev_init(struct cdev *, const struct file_operations *);
    //struct cdev *cdev_alloc(void);
    //void cdev_put(struct cdev *p);
    //int cdev_add(struct cdev *, dev_t, unsigned count);

    cdev_init(&st_Cdevive, &my_device_fops);
    retval = cdev_add(&st_Cdevive, dev, 1);
    if(retval == 0)
        printk("cdev_add\n");
    else
    {
        // delete allocated device
        unregister_chrdev_region(dev,0);
        printk("error cdev_add\n");
        return -1;
    }

    // generate file (class -device)
    //device_create(const struct class *cls, struct device *parent, dev_t devt,
	//      void *drvdata, const char *fmt, ...);

    if( (mydevice_class = class_create("test_class")) == NULL)
    {
        unregister_chrdev_region(dev,0);
        printk("error create class\n");
        cdev_del(&st_Cdevive);
        return -1;
    }
    mydevice = device_create(mydevice_class,NULL, dev,NULL, "test_dev_file"); 
    if(mydevice == NULL)
    {
        class_destroy(mydevice_class);
        unregister_chrdev_region(dev,0);
        printk("error create device\n");
        cdev_del(&st_Cdevive);
        return -1;

    }

    return 0;
}

static void __exit Add_Device_exit(void)
{
    //extern void unregister_chrdev_region(dev_t, unsigned);
    class_destroy(mydevice_class);
    cdev_del(&st_Cdevive);
    device_destroy(mydevice_class, dev);
    unregister_chrdev_region(dev,0);
    printk("Bye alloc_chrdev_region Device exit\n");
}

module_init(Add_Device_init);
module_exit(Add_Device_exit);