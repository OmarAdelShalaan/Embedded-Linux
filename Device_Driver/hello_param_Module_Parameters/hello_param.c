#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>

// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Omar Adel Shalaan");
MODULE_DESCRIPTION("A simple hello param driver");

int count = 0;
//module_param(count, int, 0);
//module_param(count, int, permission);
module_param(count, int, 0644);
MODULE_PARM_DESC(count, "An integer parameter that print the count");


static int __init hello_param_kernel_init(void)
{
    int i;
    for(i = 0; i < count; i++)
        printk("Hello param Kernel init\n");
    return 0;
}

static void __exit hello_param_kernel_exit(void)
{
    int i;
    for(i = 0; i < count; i++)
        printk("Bye param Kernel exit\n");
}

module_init(hello_param_kernel_init);
module_exit(hello_param_kernel_exit);
