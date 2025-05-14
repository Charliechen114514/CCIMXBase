#include <linux/module.h>  
#include <linux/init.h>

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Charliechen<725610365@qq.com>");
MODULE_DESCRIPTION("A simple Linux kernel module to export functions");
MODULE_VERSION("1.0");

static int my_special_int = 0;
module_param(my_special_int, int, 0660);
MODULE_PARM_DESC(my_special_int, "A demo integer parameter");

static char *my_special_str = "default";
module_param(my_special_str, charp, 0660);
MODULE_PARM_DESC(my_special_str, "A demo string parameter");

static int __init paramspass_init(void)
{
    pr_info("module parameters passed: my_special_int=%d my_special_str=%s\n",
        my_special_int, my_special_str);
    return 0;		/* success */
}

static void __exit paramspass_exit(void)
{
    pr_info("removed\n");
}

module_init(paramspass_init);
module_exit(paramspass_exit);


