#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include "plt_ap3216creg.h"
#include "driver_base.h"
#include "ap3216c.h"

typedef struct {
    IMX6ULLCharDeviceBase_t     base;
    /* promise the data transfer the same */
    void*                       iic_handle;
    AP3216CData                 cached_data;
}AP3216C_DriverData;

static AP3216C_DriverData ap3216c;

#define AP3216C_NAME        "ap3216c"
#define SINGLE_TRANS_MAX    (256)
static int ap3216c_readdatareg(
    AP3216C_DriverData* dev, u8 reg, void* value, int len)
{
    struct i2c_msg msg[2];
    struct i2c_client* client = (struct i2c_client*)dev->iic_handle;

    msg[0].addr = client->addr;
    msg[0].flags = 0;
    msg[0].buf = &reg;
    msg[0].len = 1;

    msg[1].addr = client->addr;
    msg[1].flags = I2C_M_RD;
    msg[1].buf = value;
    msg[1].len = len;    

    int res = i2c_transfer(client->adapter, msg, 2);
    if(res == 2){
        res = 0;
    }else{
        pr_info("failed to read ii2! failed: %d reg=%06x len=%d\n", res, reg, len);
        res = EREMOTEIO;
    }

    return res;
}

static s32 
ap3216c_writeregs(
    AP3216C_DriverData* dev, 
    u8 reg, void* value, int len)
{
    u8 send_buffer[SINGLE_TRANS_MAX];
    struct i2c_msg msg;
    struct i2c_client* client = (struct i2c_client*)dev->iic_handle;

    send_buffer[0] = reg;
    memcpy(&send_buffer[1], value, len);

    msg.addr = client->addr;
    msg.flags = 0;
    msg.buf = send_buffer;
    msg.len = len + 1;    

    return i2c_transfer(client->adapter, &msg, 1);
}

static u8 ap3216c_read_reg_interface(
    AP3216C_DriverData* device, u8 reg)
{
    u8 data;
    ap3216c_readdatareg(device, reg, &data, 1);
    return data;
}

static void ap3216c_writereg_interface(
    AP3216C_DriverData* device, u8 reg, u8 value)
{
    u8 buf = value;
    ap3216c_writeregs(device, reg, &buf, 1);
}

static void analysis_readdata(AP3216C_DriverData* device)
{
#define CACHED_BUFFER_N (6)
    u8 cached_buffer[CACHED_BUFFER_N];

    for(u8 i = 0; i < CACHED_BUFFER_N; i++)
    {
        cached_buffer[i] = ap3216c_read_reg_interface(device, AP3216C_IRDATALOW + i);
    }

    if(cached_buffer[0] & 0x80){
        device->cached_data.ir = 0;
    }else{
        device->cached_data.ir = ((unsigned short)cached_buffer[1] << 2) | (cached_buffer[0] & 0X03);
    }

    device->cached_data.als = ((unsigned short)cached_buffer[3] << 8);

    if(cached_buffer[4] & 0x40){
        device->cached_data.ps = 0;
    }else{
        device->cached_data.ps = ((unsigned short)(cached_buffer[5] & 0X3F) << 4) | (cached_buffer[4] & 0X0F); 
    }
}

static int ap3216c_open(struct inode * inode, struct file* pfile)
{
    pfile->private_data = &ap3216c;

    ap3216c_writereg_interface(&ap3216c, AP3216C_SYSTEMCONG, 0x04);
    mdelay(50);
    ap3216c_writereg_interface(&ap3216c, AP3216C_SYSTEMCONG, 0X03);
    return 0;
}

static ssize_t ap3216c_read(struct file *filp, char __user *buf, size_t cnt, loff_t *off)
{
	long err = 0;
	AP3216C_DriverData* dev = (AP3216C_DriverData*)filp->private_data;
	
	analysis_readdata(dev);
	err = copy_to_user(buf, &dev->cached_data, sizeof(AP3216C_DriverData));
	return err;
}

static struct file_operations ap3216c_op = {
    .owner = THIS_MODULE,
    .open = ap3216c_open,
    .read = ap3216c_read
};

static int ap3216c_probe(struct i2c_client *client)
{
    IMX6ULLCharInit_t   init = {
        .dev_cnt = 1,
        .device_operations = &ap3216c_op,
        .name_ptr = AP3216C_NAME
    };

    int res = device_base_init(&ap3216c.base, &init);
    ap3216c.iic_handle = client;
    return !res;
}

static void ap3216c_remove(struct i2c_client *client){
    device_base_deinit(&ap3216c.base);
}

static const struct i2c_device_id ap3216c_id[] = {
	{"charlies, ap3216c", 0},  
	{}
};

/* 设备树匹配列表 */
static const struct of_device_id ap3216c_of_match[] = {
	{ .compatible = "charlies, ap3216c" },
	{ /* Sentinel */ }
};

/* i2c驱动结构体 */	
static struct i2c_driver ap3216c_driver = {
	.probe = ap3216c_probe,
	.remove = ap3216c_remove,
	.driver = {
			.owner = THIS_MODULE,
		   	.name = "ap3216c",
		   	.of_match_table = ap3216c_of_match, 
		   },
	.id_table = ap3216c_id,
};


static int __init ap3216c_init(void)
{
    return i2c_add_driver(&ap3216c_driver);
}

static void __exit ap3216c_exit(void)
{
    i2c_del_driver(&ap3216c_driver);
}

MODULE_DESCRIPTION("A simple LED driver using base module");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Charliechen114514<charliechen114514@demo.com>");
MODULE_LICENSE("GPL");

module_init(ap3216c_init);
module_exit(ap3216c_exit);









