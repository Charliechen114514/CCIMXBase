#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_address.h>
#include "driver_base.h"
#include "key.h"

#define KEY_CNT         (1)

typedef struct {
    IMX6ULLCharDeviceBase_t base;
    int                     key_gpio_n;
    struct device_node*     dev_node;
    atomic_t                key_value;
}CharliesKey;

static CharliesKey  key;

static u8 fetch_from_devtree(CharliesKey* _key)
{
    atomic_set(&_key->key_value, KEY_UNPRESSED);
    _key->dev_node = of_find_node_by_path("/charlies_key");
    if(!_key->dev_node){
        pr_err("Failed to find node in dev_tree!\n");
        return -ENODEV;
    }else{
        pr_info("Successfully fetch node in dev_tree\n");
    }

    _key->key_gpio_n = of_get_named_gpio(_key->dev_node, "charlieskey-gpio", 0);
    if(_key->key_gpio_n < 0){
        pr_err("Failed to fetch gpio node in dev_tree!\n");
        return -EINVAL;
    }else{
        pr_info("Successfully fetch gpio node in dev_tree!get index: %d\n", _key->key_gpio_n);
    }

    if(gpio_request(_key->key_gpio_n, "key0")){
        pr_err("GPIO request failed\n");
        return -EBUSY;        
    }

    gpio_direction_input(_key->key_gpio_n);
    return 0;
}

static int key_open(struct inode *inode, struct file *filp) 
{
    filp->private_data = &key;

    return fetch_from_devtree(&key);
}

static ssize_t 
key_read(   struct file *filp, char __user *buf,  
            size_t cnt, loff_t *offt) 
{
    CharliesKey* thiskey = filp->private_data;
    
    if(gpio_get_value(thiskey->key_gpio_n) == 0){
        while(gpio_get_value(thiskey->key_gpio_n) == 0);
        atomic_set(&thiskey->key_value, KEY_PRESSED);
    }else{
        atomic_set(&thiskey->key_value, KEY_UNPRESSED);
    }


    int ret_to_user = atomic_read(&thiskey->key_value);
    return copy_to_user(buf, &ret_to_user, sizeof(ret_to_user));
}

static struct file_operations key_fops = { 
    .owner = THIS_MODULE,
    .open = key_open,
    .read = key_read
};


static int __init charlieskey_init(void)
{
    IMX6ULLCharInit_t   init = {
        .dev_cnt = KEY_CNT,
        .device_operations = &key_fops,
        .name_ptr = KEY_NAME
    };

    if(!device_base_init(&key.base, &init)){
        pr_err("Failed to init the base device!\n");
    }else{
        pr_info("init issue down!");
    }

    return 0;
}

static void __exit charlieskey_exit(void)
{
    gpio_free(key.key_gpio_n);
    device_base_deinit(&key.base);
}

module_init(charlieskey_init);
module_exit(charlieskey_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("charliechen<charliechen@demo.com>");

