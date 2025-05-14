#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Charliechen<725610365@qq.com>");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("A simple hello world module");
MODULE_VERSION("1.0");

static __init int hello_init(void)
{
    pr_info("Hello, world!\n");
    return 0;
}

static __exit void hello_exit(void)
{
     pr_info("Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);
