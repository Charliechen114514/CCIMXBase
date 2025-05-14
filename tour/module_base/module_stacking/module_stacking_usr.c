#include <linux/init.h>
#include <linux/module.h>
#include "common_keys.h"
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Charliechen<725610365@qq.com>");
MODULE_DESCRIPTION("A simple Linux kernel module to use exported functions");
MODULE_VERSION("1.0");

/* externed values */
extern int global_vars;
extern void display_sys_info(void);
extern u8 auth_key(u32 keys);

static void process(void)
{
    if(auth_key(MY_KEY)){
        pr_info("Auth success!");
    }else{
        pr_err("Auth failed");
    }

    pr_info("We have fetch the vars in global: %d\n", global_vars);
    display_sys_info();
}


static int __init user_init(void)
{
    process();
    return 0;
}

static void __exit user_exit(void)
{
    pr_info("Goodbye!\n");
}

module_init(user_init);
module_exit(user_exit);

