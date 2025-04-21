#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>
#include "misc_beep.h"

#define BEEP_DEVTREE_NAME_ROOT  "charlies_beep"
#define BEEP_GPIO_PROPERTY      "charliesbeep-gpio"
#define BEEP_MINOR      (114)
#define BEEPON_GPIO     (0)
#define BEEPOFF_GPIO    (1)

typedef struct  {
    struct device_node *device_node;
    int beep_gpio;
    /* misc requires the minor differs */
    int beep_minor;
}CharliesBeep;

static CharliesBeep beep;

static inline void set_beep_status(const CharliesBeep* beep, int value)
{
    gpio_set_value(beep->beep_gpio, value);
    return;
}

static int beep_open(struct inode* node, struct file* filp)
{
    /* offer the device */
    filp->private_data = &beep;
    return 0;
}

static ssize_t
beep_read(struct file *filp, char *buffer, size_t count, loff_t *ppos)
{
    int ret = 0;
    const char *status = BEEP_ST_OPEN;
    int gpio_current_value = 0;
    pr_info("Triggering the read gpio status of beep!\n");
    gpio_current_value = gpio_get_value(beep.beep_gpio);
    if (gpio_current_value == BEEPOFF_GPIO)
    {
        status = BEEP_ST_CLOSE;
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
beep_write(struct file *filp, const char *buffer, size_t count, loff_t *ppos)
{
    int check = 0;
    CharliesBeep *dev = filp->private_data;
    pr_info("\nled device is ready writing!\n");
    check = copy_from_user(operations_cached, buffer, count);
    if (check < 0)
    {
        pr_warn("Can not copy from user!\n");
        return -EFAULT;
    }

    if (!strcmp(operations_cached, BEEPON_CMD))
    {
        set_beep_status(dev, BEEPON_GPIO);
    }
    else if (!strcmp(operations_cached, BEEPOFF_CMD))
    {
        set_beep_status(dev, BEEPOFF_GPIO);
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

static struct file_operations beep_op = {
    .owner = THIS_MODULE,
    .open = beep_open,
    .write = beep_write,
    .read = beep_read
};

static struct miscdevice beep_device = {
    .fops = &beep_op,
    .minor = BEEP_MINOR,
    .name = "charlies_beep"
};


static int fetch_node_from_dev_tree(CharliesBeep* beep)
{
    pr_info("Attempt to fetch the node in the device tree!\r\n");
    beep->device_node = of_find_node_by_path("/"BEEP_DEVTREE_NAME_ROOT);
    if(!beep->device_node)
    {
        pr_err("error in fetching node in the root: %s\r\n", BEEP_DEVTREE_NAME_ROOT);
        return 0;
    }else{
        pr_info("fetch the node in the device tree!\r\n");
    }

    beep->beep_gpio = of_get_named_gpio(beep->device_node, BEEP_GPIO_PROPERTY, 0);
    if(beep->beep_gpio < 0)
    {
        pr_err("error in fetching node in the root: %s\r\n", BEEP_DEVTREE_NAME_ROOT);
        return 0;
    }else{
        pr_info("fetch the node property in the device tree!\r\n");
    }

    pr_info(
        "Now we get the beep gpio number handle: %d!\r\n"
        "Default we shell set the behaviour of beep is: ",
        beep->beep_gpio
    );
    int status = gpio_request(beep->beep_gpio, "charlies-beep");
    
    if(status)
    {
        pr_err("failed to request the gpio!\n");
    }else{
        pr_info("request the gpio success!\n");
    }

#if BEEP_DEF_BEHAVE
    pr_info("ON!\r\n");
    int ret = gpio_direction_output(beep->beep_gpio, BEEPON_GPIO);
    if (ret) {
        pr_err("Failed to set GPIO direction\n");
    }
#else
    pr_info("OFF!\r\n");
    int ret = gpio_direction_output(beep->beep_gpio, BEEPOFF_GPIO);
    if (ret) {
        pr_err("Failed to set GPIO direction\n");
    }
#endif
    pr_info("fetch beep init finished!\r\n");
    return 1;
}

static int charliesbeep_probe(struct platform_device* dev)
{
    if(!fetch_node_from_dev_tree(&beep)){
        return -EINVAL;
    }

    int res = misc_register(&beep_device);
    if(res < 0){
        pr_err("misc device register failed!\r\n"); 
        return -EFAULT; 
    }
    return 0;
}

static void charliesbeep_remove(struct platform_device* dev)
{
    pr_info("Entering the beep release!\r\n");
    set_beep_status(&beep, BEEPOFF_GPIO);
    gpio_free(beep.beep_gpio);
    misc_deregister(&beep_device);
    pr_info("See you next time beep!\r\n");
}

static const struct of_device_id charliesbeep_match[] = {
    {.compatible = "charlies_beep"},
    {}
};

static struct platform_driver charliesbeep_driver = {
    .driver = {
        .of_match_table = charliesbeep_match,
        .name = "charlies-beep"
    },
    .probe = charliesbeep_probe,
    .remove = charliesbeep_remove
};


static int __init charliesbeep_init(void)
{
    return platform_driver_register(&charliesbeep_driver);
}

/* exit the module using rmmod */
static void __exit charliesbeep_exit(void)
{
    return platform_driver_unregister(&charliesbeep_driver);
}

MODULE_DESCRIPTION("A simple beep driver using base module");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Charliechen114514<charliechen114514@demo.com>");
MODULE_LICENSE("GPL");

module_init(charliesbeep_init);
module_exit(charliesbeep_exit);










