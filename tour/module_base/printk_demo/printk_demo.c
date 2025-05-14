#include <linux/init.h>
#include <linux/module.h>

static void display_pr_level(void)
{
    pr_emerg("This is a pr_emerg message.\n");
    pr_alert("This is a pr_alert message.\n");
    pr_crit("This is a pr_crit message.\n");
    pr_err("This is a pr_err message.\n");
    pr_warn("This is a pr_warn message.\n");
    pr_notice("This is a pr_notice message.\n");
    pr_info("This is a pr_info message.\n");   
    pr_debug("This is a pr_debug message.\n");
    pr_devel("This is a pr_devel message.\n");
}

static int __init printk_demo_init(void)
{
    pr_info("printk_demo module loaded.\n");
    display_pr_level();
    return 0;
}
static void __exit printk_demo_exit(void)
{
    pr_info("printk_demo module unloaded.\n");
}

module_init(printk_demo_init);
module_exit(printk_demo_exit);
MODULE_AUTHOR("Charliechen<725610365@qq.com>");
MODULE_LICENSE("Dual MIT/GPL");
MODULE_DESCRIPTION("A simple printk demo module");
MODULE_VERSION("1.0");





