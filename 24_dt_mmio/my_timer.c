#include<linux/module.h>
#include<linux/init.h>
#include<linux/io.h>
#include<linux/mod_devicetable.h>
#include<linux/platform_device.h>


/* Name all the compatibale devices */
static const struct of_device_id my_timer_ids[] = {

	{.compatible = "arm,my_timer"},
	{} /* Empty Element -> end of the list */
};
MODULE_DEVICE_TABLE(of, my_timer_ids);

static struct resource *res;
static u32 __iomem *hwregs;

/* Implement  a probe and a remove function */
static int my_timer_probe(struct platform_device *pdev)
{
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if(!res){
	dev_err(&pdev->dev, "Error could not get resourse\n");
	return -ENODEV;	

	}
	dev_info(&pdev->dev,"Resourse at %llx (%lld Bytes in size\n",res->start, resource_size(res));
	
	hwregs = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	if(!hwregs) {
		dev_err(&pdev->dev, "Error could not map resourse\n");
		return ENODEV;
	}
	// set Load register
	*(hwregs) =0xffff;
	
	// Enable out the timer
	*(hwregs + 2) |= (1<<7);

	//Read out the timer twice
	dev_info(&pdev->dev, "Timer value: 0x%x\n", *(hwregs +1));

	dev_info(&pdev->dev, "Timer value: 0x%x\n", *(hwregs +1));
	return 0;
}

static void my_timer_remove(struct platform_device *pdev)
{
	//Disable the timer
	*(hwregs +2) &= (1<<7);
	pr_info("my_timer - Remove Function is called \n");
	
}
/* Bundle compatible devices, probe and remove in driver's struct */
static struct platform_driver my_timer_driver ={

	.probe = my_timer_probe,
	.remove = my_timer_remove,
        .driver = {
			.name = "my_timer_driver",
			.of_match_table = my_timer_ids,
	}	
};

/* Register the driver at the os */


module_platform_driver(my_timer_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raushan Kumar");
MODULE_DESCRIPTION("Driver for Rpi ARM Timer");



