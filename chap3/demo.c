#include <linux/module.h>
#include <linux/init.h>
#include <linux/kallsyms.h> // kallsyms_lookup_name
#include <linux/syscalls.h> // SYSCALL_DEFINEx
#include <linux/moduleparam.h>

#ifndef NR_syscalls
#define NR_syscalls 448
#endif

int demo_sc_nr = -1;
module_param(demo_sc_nr, int, 0444); // 只读

// 创建一个系统调用
int create_syscall(unsigned long syscall_addr)
{
    // 查找sys_call_table的地址
    unsigned long *sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
    if (!sys_call_table) {
        printk("kallsyms_lookup_name failed\n");
        return -1;
    }

    // 查找sys_ni_syscall的地址
    unsigned long sys_ni_syscall = (unsigned long)kallsyms_lookup_name("sys_ni_syscall");
    if (!sys_ni_syscall) {
        printk("kallsyms_lookup_name failed\n");
        return -1;
    }

    // 查找sys_call_table中的空闲位置
    int i = 0;
    for (i = 0; i < NR_syscalls; i++) {
        if (sys_call_table[i] == sys_ni_syscall) {
            demo_sc_nr = i;
            break;
        }
    }
    if (i == NR_syscalls) {
        printk("no free syscall\n");
        return -1;
    }

    // 检查sys_call_talbe[i]的读写属性
    unsigned int level;
    pte_t old_pte, *pte = lookup_address((unsigned long)&sys_call_table[i], &level);
    if (!pte || level != PG_LEVEL_4K) {
        printk("lookup_address failed\n");
        return -1;
    }
    old_pte = *pte;
    // 修改sys_call_table[i]的读写属性 
    if (pte->pte & ~_PAGE_RW) {
        pte->pte |= _PAGE_RW;
    }
    // 将sys_call_table[i]指向demo_syscall
    sys_call_table[i] = syscall_addr;
    // 恢复sys_call_table[i]的读写属性
    *pte = old_pte;

    return 0;
}

static int __init demo_init(void)
{
    printk("demo init\n");   

    return 0;
}

static void __exit demo_exit(void)
{
    printk("demo_exit\n");
    
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("shengbangwu");
MODULE_DESCRIPTION("demo");
