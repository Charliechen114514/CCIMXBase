#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include "plt_icm20608reg.h"
#include "driver_base.h"
#include "icm20608.h"

typedef struct
{
    IMX6ULLCharDeviceBase_t base;
    /* promise the data transfer the same */
    void *spi_handle;
    ICM20608Data cached_data;
} ICM20608_DriverData;

static ICM20608_DriverData icm20608;

#define ICM20608_NAME "icm20608"
#define SINGLE_TRANS_MAX (256)

static int icm20608_read_register_impl(
    ICM20608_DriverData *device, u8 reg, void *buf, int len)
{
    struct spi_transfer *transfer =
        kzalloc(sizeof(struct spi_transfer), GFP_KERNEL);
    if (!transfer)
    {
        pr_err("error in allocating transfer buffer!\n");
        return -ENOMEM;
    }

    u8 *rxdata = kzalloc(sizeof(u8) * len, GFP_KERNEL);

    if (!rxdata)
    {
        pr_err("error in allocating receiving buffer!\n");
        goto icm20608_free_the_transfer_data_rx;
    }

    u8 txdata = reg | 0x80;
    transfer->tx_buf = &txdata;
    transfer->rx_buf = rxdata;
    transfer->len = len + 1;

    struct spi_message message;
    spi_message_init(&message);
    spi_message_add_tail(transfer, &message);

    struct spi_device *spi = (struct spi_device *)device->spi_handle;
    int result = spi_sync(spi, &message);
    if (result)
    {
        pr_err("error in syncing the spi message!\n");
        goto icm20608_free_the_rxdata;
    }

    /* copy out the info */
    memcpy(buf, rxdata + 1, len);

icm20608_free_the_rxdata:
    kfree(rxdata);
icm20608_free_the_transfer_data_rx:
    kfree(transfer);

    return 0;
}

static s32 icm20609_write_register_impl(
    ICM20608_DriverData *device,
    u8 reg, u8 *buf, u8 len)
{
    struct spi_transfer *transfer =
        kzalloc(sizeof(struct spi_transfer), GFP_KERNEL);
    if (!transfer)
    {
        pr_err("error in allocating transfer buffer!\n");
        return -ENOMEM;
    }

    u8 *txdata = kzalloc(sizeof(char) + len, GFP_KERNEL);
    if (!txdata)
    {
        pr_err("Error in allocating the send buffer!\n");
        goto icm20608_free_the_transfer_data_tx;
    }

    txdata[0] = reg & ~0x80;
    memcpy(txdata + 1, buf, len);
    transfer->tx_buf = txdata;
    transfer->len = len + 1;
    struct spi_message message;
    spi_message_init(&message);
    spi_message_add_tail(transfer, &message);

    struct spi_device *spi = (struct spi_device *)device->spi_handle;
    int result = spi_sync(spi, &message);
    kfree(txdata);
icm20608_free_the_transfer_data_tx:
    kfree(transfer);
    return result;
}

static u8
icm20608_read_singlereg(
    ICM20608_DriverData *device, u8 reg)
{
    u8 data;
    icm20608_read_register_impl(
        device, reg, &data, 1);
    return data;
}

static void
icm20608_write_singlereg(
    ICM20608_DriverData *device,
    u8 reg, u8 value)
{
    u8 buf = value;
    icm20609_write_register_impl(device, reg, &buf, 1);
}

static void process_once_read(
    ICM20608_DriverData* device)
{
#define SPI_DATAS_N   (14)
	unsigned char data[14] = { 0 };
	icm20608_read_register_impl(device, ICM20608_ACCEL_XOUT_H, data, 14);
#undef SPI_DATAS_N

    device->cached_data.g_acc.x = (signed short)((data[0] << 8) | data[1]); 
	device->cached_data.g_acc.y = (signed short)((data[2] << 8) | data[3]); 
	device->cached_data.g_acc.z = (signed short)((data[4] << 8) | data[5]); 
	device->cached_data.rol.x  = (signed short)((data[8] << 8) | data[9]); 
	device->cached_data.rol.y  = (signed short)((data[10] << 8) | data[11]);
	device->cached_data.rol.z  = (signed short)((data[12] << 8) | data[13]);
    device->cached_data.temperature = (signed short)((data[6] << 8) | data[7]); 
}


static int icm20608_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &icm20608;
    return 0;
}

static ssize_t icm20608_read(struct file *filp, char __user *buf, size_t cnt, loff_t *off)
{
    ICM20608_DriverData* device = (ICM20608_DriverData*)filp->private_data;
    process_once_read(device);
    return copy_to_user(buf, &device->cached_data, sizeof(device->cached_data));
}

static struct file_operations icm20608_op = {
    .owner = THIS_MODULE,
	.open = icm20608_open,
	.read = icm20608_read
};

static void init_icm20608_register(ICM20608_DriverData* device)
{
	u8 value = 0;
	
	icm20608_write_singlereg(device, ICM20608_PWR_MGMT_1, 0x80);
	mdelay(50);
	icm20608_write_singlereg(device, ICM20608_PWR_MGMT_1, 0x01);
	mdelay(50);

	value = icm20608_read_singlereg(device, ICM20608_WHO_AM_I);
	printk("ICM20608 ID = %#X\r\n", value);	

	icm20608_write_singlereg(device, ICM20608_SMPLRT_DIV, 0x00); 	/* 输出速率是内部采样率					*/
	icm20608_write_singlereg(device, ICM20608_GYRO_CONFIG, 0x18); 	/* 陀螺仪±2000dps量程 				*/
	icm20608_write_singlereg(device, ICM20608_ACCEL_CONFIG, 0x18); 	/* 加速度计±16G量程 					*/
	icm20608_write_singlereg(device, ICM20608_CONFIG, 0x04); 		/* 陀螺仪低通滤波BW=20Hz 				*/
	icm20608_write_singlereg(device, ICM20608_ACCEL_CONFIG2, 0x04); /* 加速度计低通滤波BW=21.2Hz 			*/
	icm20608_write_singlereg(device, ICM20608_PWR_MGMT_2, 0x00); 	/* 打开加速度计和陀螺仪所有轴 				*/
	icm20608_write_singlereg(device, ICM20608_LP_MODE_CFG, 0x00); 	/* 关闭低功耗 						*/
	icm20608_write_singlereg(device, ICM20608_FIFO_EN, 0x00);		/* 关闭FIFO						*/
}

static int icm20608_probe(struct spi_device *spi)
{
    pr_info("prepare to probe!\n");
    IMX6ULLCharInit_t init = {
        .dev_cnt = 1,
        .name_ptr = ICM20608_NAME,
        .device_operations = &icm20608_op
    };
    device_base_init(&icm20608.base, &init);

    spi->mode = SPI_MODE_0;
    spi_setup(spi);
    icm20608.spi_handle = spi;

    init_icm20608_register(&icm20608);

    return 0;
}

static void icm20608_remove(struct spi_device *spi)
{
    device_base_deinit(&icm20608.base);
}

static const struct spi_device_id icm20608_id[] = {
	{"icm20608", 0},  
	{}
};

static const struct of_device_id icm20608_of_match[] = {
	{ .compatible = "charliechen,icm20608" },
	{}
};

static struct spi_driver icm20608_driver = {
	.probe = icm20608_probe,
	.remove = icm20608_remove,
	.driver = {
			.owner = THIS_MODULE,
		   	.name = "icm20608",
		   	.of_match_table = icm20608_of_match, 
		   },
	.id_table = icm20608_id,
};

static int __init icm20608_init(void)
{
	return spi_register_driver(&icm20608_driver);
}

static void __exit icm20608_exit(void)
{
	spi_unregister_driver(&icm20608_driver);
}

module_init(icm20608_init);
module_exit(icm20608_exit);
MODULE_DESCRIPTION("A simple ICM20608 driver using base module");
MODULE_VERSION("1.0");
MODULE_AUTHOR("Charliechen114514<charliechen114514@demo.com>");
MODULE_LICENSE("GPL");

