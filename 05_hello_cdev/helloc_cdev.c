#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>



static int major;

static ssize_t my_read (struct file *f, char __user *u, size_t l, loff_t *o)
{
	printk("Read is called");
	return 0;
}
static struct file_operations fops={

	.read=my_read
};

static int __init my_init(void)
{
	major = register_chrdev(0, "hello_cdev", &fops); //allcate available device number dynamic allocarion
	
        if(major<0){

		printk("hello_cdev - Error registering chardev \n");
	}
	printk("hello_cdev -Major Device Number :%d\n",major);
       
        return 0;

}

static void __exit my_exit(void)
{

	unregister_chrdev(major, "hello_cdev");
}
module_init(my_init);
module_exit(my_exit);







MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raushan Kumar");
MODULE_DESCRIPTION("A Simple driver for registring a character device");



