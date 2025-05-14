#include <linux/init.h>
#include <linux/module.h>
#include "common_keys.h"
MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Charliechen<725610365@qq.com>");
MODULE_DESCRIPTION("A simple Linux kernel module to export functions");
MODULE_VERSION("1.0");

/* export the symbols */
int global_vars = 114514;
EXPORT_SYMBOL(global_vars);

u8 auth_key(u32 keys);
void display_sys_info(void);

static void show_sizeof(void)
{
	pr_info("types size in IMX6ULL: \n"
		"  char = %2zu   short int = %2zu              int = %2zu\n"
		"  long = %2zu   long long = %2zu           void * = %2zu\n"
		" float = %2zu      double = %2zu      long double = %2zu\n",
		sizeof(char), sizeof(short int),
		sizeof(int), sizeof(long), sizeof(long long), sizeof(void *),
		sizeof(float), sizeof(double), sizeof(long double));
}

static void show_max(void)
{
	/* Word ranges: min & max: defines are in include/linux/limits.h */
	pr_info
	    ("Word [U|S][8|16|32|64] ranges: unsigned max, signed max, signed min:\n"
	     " U8_MAX = %20u = 0x%16x,  S8_MAX = %20d = 0x%16x,  S8_MIN = %20d = 0x%16x\n"
	     "U16_MAX = %20u = 0x%16x, S16_MAX = %20d = 0x%16x, S16_MIN = %20d = 0x%16x\n"
	     "U32_MAX = %20u = 0x%16x, S32_MAX = %20d = 0x%16x, S32_MIN = %20d = 0x%16x\n"
	     "U64_MAX = %20llu = 0x%16llx, S64_MAX = %20lld = 0x%16llx, S64_MIN = %20lld = 0x%16llx\n"
#if (BITS_PER_LONG == 32)
	      "PHYS_ADDR_MAX = %u = 0x%px\n"
#else
	      "PHYS_ADDR_MAX = %llu = 0x%px\n"
#endif
	     , U8_MAX, U8_MAX, S8_MAX, S8_MAX, S8_MIN, S8_MIN,
	     U16_MAX, U16_MAX, S16_MAX, S16_MAX, S16_MIN, S16_MIN,
	     U32_MAX, U32_MAX, S32_MAX, S32_MAX, S32_MIN, S32_MIN,
	     U64_MAX, U64_MAX, S64_MAX, S64_MAX, S64_MIN, S64_MIN
	     , PHYS_ADDR_MAX, (void *)PHYS_ADDR_MAX);    
}

/* common library info */
void display_sys_info(void)
{
#ifdef CONFIG_ARM
    pr_info("Platform locates in ARM\n");
#else
    pr_info("Platform locates in Other\n");
#endif

#if (BITS_PER_LONG == 32)
    pr_info("32bits wide platform!\n");
#else 
    pr_info("64bits wide platform!\n");
#endif
    show_sizeof();
    show_max();
}
EXPORT_SYMBOL(display_sys_info);

/* params passing test */
u8 auth_key(u32 keys)
{
    return keys == MY_KEY;
}
EXPORT_SYMBOL(auth_key);

static int __init library_init(void){
    pr_info("Requires Sysbols Already Exported!\n");
    return 0;
}

static void __exit library_exit(void){
    pr_info("Requires Sysbols Already Unexported!\n");
}

module_init(library_init);
module_exit(library_exit);


