#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/errno.h>

#define IO_LED     21
#define IO_BUTTON  20
#define IO_OFFSET  512   /* board-specific, NOT portable */

static int led_gpio;
static int button_gpio;

static int __init my_init(void)
{
    int status;
    int btn_val;
    
    pr_info("gpioctrl: init\n");
    
    led_gpio = IO_LED + IO_OFFSET;
    button_gpio = IO_BUTTON + IO_OFFSET;
    
    /* Request and configure LED GPIO */
    status = gpio_request(led_gpio, "led");
    if (status) {
        pr_err("gpioctrl: Failed to request LED GPIO %d\n", led_gpio);
        return status;
    }
    
    status = gpio_direction_output(led_gpio, 0);
    if (status) {
        pr_err("gpioctrl: Failed to set LED as output\n");
        gpio_free(led_gpio);
        return status;
    }
    
    /* Request and configure Button GPIO */
    status = gpio_request(button_gpio, "button");
    if (status) {
        pr_err("gpioctrl: Failed to request Button GPIO %d\n", button_gpio);
        gpio_free(led_gpio);
        return status;
    }
    
    status = gpio_direction_input(button_gpio);
    if (status) {
        pr_err("gpioctrl: Failed to set Button as input\n");
        gpio_free(button_gpio);
        gpio_free(led_gpio);
        return status;
    }
    
    /* Read button value and set LED */
    btn_val = gpio_get_value(button_gpio);
    gpio_set_value(led_gpio, btn_val);
    
    pr_info("gpioctrl: Button is %spressed\n",
            btn_val ? "" : "not ");
    
    return 0;
}

static void __exit my_exit(void)
{
    gpio_set_value(led_gpio, 0);
    gpio_free(button_gpio);
    gpio_free(led_gpio);
    pr_info("gpioctrl: exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raushan Kumar");
MODULE_DESCRIPTION("GPIO example without device tree (educational only)");
