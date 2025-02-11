#include <linux/module.h>
#include <linux/init.h>

#include <linux/moduleparam.h>
#include <linux/wait.h>

#include "common.h"

static int __init demo_init(void)
{
    printk("demo init\n");   

    return 0;
}



static void __exit demo_exit(void)
{
    printk("demo_exit\n");

    if (demo_wait_nr > 0) {
        remove_syscall(demo_wait_nr);
    }
    if (demo_wakeup_nr > 0) {
        remove_syscall(demo_wakeup_nr);
    }


}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("shengbangwu");
MODULE_DESCRIPTION("demo");
