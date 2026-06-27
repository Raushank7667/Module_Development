#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/errno.h>

#define IO_LED     21
#define IO_BUTTON  20
#define IO_OFFSET  512    /* Board-specific */

static int led_gpio;
static int button_gpio;
static int irq_number;

/* Interrupt Service Routine */
static irqreturn_t button_isr(int irq, void *dev_id)
{
    int btn_val;

    btn_val = gpio_get_value(button_gpio);

    gpio_set_value(led_gpio, btn_val);

    pr_info("gpioctrl: Button %s\n",
            btn_val ? "pressed" : "released");

    return IRQ_HANDLED;
}

static int __init my_init(void)
{
    int status;

    pr_info("gpioctrl: init\n");

    led_gpio = IO_LED + IO_OFFSET;
    button_gpio = IO_BUTTON + IO_OFFSET;

    /* Request LED GPIO */
    status = gpio_request(led_gpio, "led");
    if (status) {
        pr_err("gpioctrl: Failed to request LED GPIO %d\n",
               led_gpio);
        return status;
    }

    /* Configure LED as output */
    status = gpio_direction_output(led_gpio, 0);
    if (status) {
        pr_err("gpioctrl: Failed to set LED as output\n");
        gpio_free(led_gpio);
        return status;
    }

    /* Request Button GPIO */
    status = gpio_request(button_gpio, "button");
    if (status) {
        pr_err("gpioctrl: Failed to request Button GPIO %d\n",
               button_gpio);
        gpio_free(led_gpio);
        return status;
    }

    /* Configure Button as input */
    status = gpio_direction_input(button_gpio);
    if (status) {
        pr_err("gpioctrl: Failed to set Button as input\n");
        gpio_free(button_gpio);
        gpio_free(led_gpio);
        return status;
    }

    /* Convert GPIO to IRQ */
    irq_number = gpio_to_irq(button_gpio);
    if (irq_number < 0) {
        pr_err("gpioctrl: Failed to map GPIO to IRQ\n");
        gpio_free(button_gpio);
        gpio_free(led_gpio);
        return irq_number;
    }

    pr_info("gpioctrl: GPIO %d mapped to IRQ %d\n",
            button_gpio, irq_number);

    /* Request interrupt on both rising and falling edges */
    status = request_irq(irq_number,
                         button_isr,
                         IRQF_TRIGGER_RISING |
                         IRQF_TRIGGER_FALLING,
                         "button_irq",
                         NULL);

    if (status) {
        pr_err("gpioctrl: Failed to request IRQ %d\n",
               irq_number);
        gpio_free(button_gpio);
        gpio_free(led_gpio);
        return status;
    }

    pr_info("gpioctrl: Interrupt registered successfully\n");

    return 0;
}

static void __exit my_exit(void)
{
    free_irq(irq_number, NULL);

    gpio_set_value(led_gpio, 0);

    gpio_free(button_gpio);
    gpio_free(led_gpio);

    pr_info("gpioctrl: exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raushan Kumar");
MODULE_DESCRIPTION("GPIO Button Interrupt Example");

