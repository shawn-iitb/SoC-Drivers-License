#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_AUTHOR("<lol DONT insert your name here XD>");
MODULE_DESCRIPTION("LKP book:ch4/q5: hello, world, our first LKM");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_VERSION("0.1");

static int __init helloworld_lkm_init(void)
{
	printk(KERN_INFO "Hello Linux, my love >3\n");
	return 0;		/* success */
}

static void __exit helloworld_lkm_exit(void)
{
	printk(KERN_INFO "Byeee Linux, ill miss youuu )::\n");
}

module_init(helloworld_lkm_init);
module_exit(helloworld_lkm_exit);
