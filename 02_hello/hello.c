#include<linux/module.h>
#include<linux/init.h>

static int __init my_init(void)
{
	printk("hello kernel!\n");
        return 0;

}

static void __exit my_exit(void)
{
	printk("By By Good by Kernel!\n");
}
module_init(my_init);
module_exit(my_exit);







MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raushan Kumar");
MODULE_DESCRIPTION("A Simple Hello World Linux Kernel Module");



