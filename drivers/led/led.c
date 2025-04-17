#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>

#include "driver_base.h"
#include "led.h"
typedef struct
{
    IMX6ULLCharDeviceBase_t device_internal;
    /* device node ptr in device tree */
    struct device_node *device_node;
    int led_gpio_n;
} CharliesLED;

static CharliesLED charlies_led;


static void set_led_status(const CharliesLED* led, int value)
{
    gpio_set_value(led->led_gpio_n, value);

    return;
}

static int
led_open(struct inode *inode, struct file *filp)
{
    /* make no sense in led */
    filp->private_data = &charlies_led;
    pr_info("\r\nopen the deviced by application\r\n");
    return 0;
}

static ssize_t
led_read(struct file *filp, char *buffer, size_t count, loff_t *ppos)
{
    int ret = 0;
    const char *status = K_LED_STATUS_OPEN;
    int gpio_current_value = 0;
    pr_info("Triggering the read gpio status of led!\n");
    gpio_current_value = gpio_get_value(charlies_led.led_gpio_n);
    if (gpio_current_value == LED_OFF_VALUE)
    {
        status = K_LED_STATUS_CLOSED;
    }
    ret = copy_to_user(buffer, status, strlen(status));
    if (ret < 0)
    {
        pr_warn("Copy to the user failed\n");
        return -EFAULT;
    }
    return 0;
}

static char operations_cached[20];
static ssize_t
led_write(struct file *filp, const char *buffer, size_t count, loff_t *ppos)
{
    int check = 0;
    CharliesLED *dev = filp->private_data;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if (check < 0)
    {
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if (!strcmp(operations_cached, K_LED_OPEN_CMD))
    {
        set_led_status(dev, LED_ON_VALUE);
    }
    else if (!strcmp(operations_cached, K_LED_CLOSE_CMD))
    {
        set_led_status(dev, LED_OFF_VALUE);
    }
    else
    {
        pr_warn("Can not find the indications operations!\n"
                "check the business: %s",
                operations_cached);
    }
    memset(operations_cached, 0, 20);
    return 0;
}

static int
led_release(struct inode *inode, struct file *filp)
{
    pr_info("\r\nrelease the device by application\r\n");
    return 0;
}

static struct file_operations led_op = {
    .open = led_open,
    .release = led_release,
    .read = led_read,
    .write = led_write};

static int fetch_node_from_dev_tree(CharliesLED* led)
{
    pr_info("Attempt to fetch the node in the device tree!\r\n");
    led->device_node = of_find_node_by_path("/"LED_NAME);
    if(!led->device_node)
    {
        pr_err("error in fetching node in the root: %s\r\n", LED_NAME);
        return 0;
    }else{
        pr_info("fetch the node in the device tree!\r\n");
    }

    led->led_gpio_n = of_get_named_gpio(led->device_node, LED_GPIO_PROPERTY, 0);
    if(led->led_gpio_n < 0)
    {
        pr_err("error in fetching node in the root: %s\r\n", LED_NAME);
        return 0;
    }else{
        pr_info("fetch the node property in the device tree!\r\n");
    }

    pr_info(
        "Now we get the led gpio number handle: %d!\r\n"
        "Default we shell set the behaviour of led is: ",
        led->led_gpio_n
    );
    int status = gpio_request(led->led_gpio_n, "charlies-led");
    
    if(status)
    {
        pr_err("failed to request the gpio!\n");
    }else{
        pr_info("request the gpio success!\n");
    }

#if LED_DEF_BEHAVE
    pr_info("ON!\r\n");
    int ret = gpio_direction_output(led->led_gpio_n, LED_ON_VALUE);
    if (ret) {
        pr_err("Failed to set GPIO direction\n");
    }
#else
    pr_info("OFF!\r\n");
    int ret = gpio_direction_output(led->led_gpio_n, LED_OFF_VALUE);
    if (ret) {
        pr_err("Failed to set GPIO direction\n");
    }
#endif
    pr_info("fetch led init finished!\r\n");
    return 1;
}

static int __init charliesled_init(void)
{
    pr_info("Start the led driving issue!\r\n");
    fetch_node_from_dev_tree(&charlies_led);
    IMX6ULLCharInit_t init_type = {
        .dev_cnt = 1,
        .name_ptr = LED_NAME,
        .device_operations = &led_op,
    };
    device_base_init(&charlies_led.device_internal, &init_type);
    pr_info("the led driving issue done!\r\n");
    return 0;
}

/* exit the module using rmmod */
static void __exit charliesled_exit(void)
{
    pr_info("Entering the led release!\r\n");
    set_led_status(&charlies_led, LED_OFF_VALUE);
    gpio_free(charlies_led.led_gpio_n);
    device_base_deinit(&charlies_led.device_internal);
    pr_info("See you next time led!\r\n");
}

MODULE_DESCRIPTION("A simple LED driver using base module");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Charliechen114514<charliechen114514@demo.com>");
MODULE_LICENSE("GPL");

module_init(charliesled_init);
module_exit(charliesled_exit);
