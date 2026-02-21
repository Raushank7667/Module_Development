#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>



static int major;


static int my_open (struct inode *inode, struct file *filp){

	pr_info("hello_cdev - Major divice no: %d ,Minor device No: %d\n", imajor(inode),iminor(inode));
	pr_info("hello_cdev - filp->f_pos: %lld\n",filp->f_pos);
	pr_info("hell0_cdev - filp->f_mode: 0x%x\n",filp->f_mode);
        pr_info("hello_cdev - filp->f_flags: 0x%x\n",filp->f_flags);

	return 0;

}

static  int my_release (struct inode *inode, struct file *filp){


        pr_info("hello_cdev - file is closed");
	return 0;
}

static struct file_operations fops={

	.open=my_open,
	.release=my_release,
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



