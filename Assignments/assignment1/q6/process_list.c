#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_AUTHOR("shon");
MODULE_DESCRIPTION("Lists all processes");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.0.0.1");


static void get_processes(void) {
    struct task_struct *p;
    int total = 0;

    for_each_process(p) {

        printk(KERN_INFO "PID: %-6d State: %-8ld Name: %-16s\n", p->pid, p->state, p->comm);

        total++;
    }
    printk(KERN_INFO "\nTotal: %d\n", total);

    return;
}


static int __init process_list_init(void) {
    printk(KERN_INFO "\nprocess_list init\n\n");

    get_processes();

    return 0;
}

static void __exit process_list_exit(void) {
    printk(KERN_INFO "\nprocess_list exit\n\n");
    return;
}

module_init(process_list_init);
module_exit(process_list_exit);