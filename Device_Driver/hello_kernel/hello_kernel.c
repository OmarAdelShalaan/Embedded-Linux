#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omar Adel Shalaan");
MODULE_DESCRIPTION("A simple hello driver");


static int __init hello_kernel_init(void)
{
    printk("Hello Kernel init\n");
    return 0;
}

static void __exit hello_kernel_exit(void)
{
    printk("Bye Kernel exit\n");
}

module_init(hello_kernel_init);
module_exit(hello_kernel_exit);

