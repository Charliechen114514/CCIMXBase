#ifndef DRIVER_BASE_H
#define DRIVER_BASE_H

/* including some neccessary components in drivers */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>

typedef struct __imx6ull_chardriver_bases{
    dev_t               device_id;              /* id of this device */
    struct device*      ker_device_handle;      /* kernel's device handle */
    struct cdev         char_device;            /* char dev types */
    struct class*       device_class;           /* device class belongs */
    u8                  device_count;
}IMX6ULLCharDeviceBase_t;

/* yeap, we pass this for the init issues */
typedef struct __imx6ull_chardevinit_requires{
    /* 
        initing requires if the device has a concrete dev number 
        so we placed an abstract here :)
    */
    int         led_dev_major;
    int         led_dev_minor;
    /* how many devices? */
    u8          dev_cnt;
    /* At what name? */
    const char* name_ptr;   /* You must promise the name is valid in init process */
    struct file_operations* device_operations;
}IMX6ULLCharInit_t;

/**
 * @brief this kind of init requires the statically, ininting the device type
 * 
 * @param ptr_base_type: stack placed ptr of IMX6ULLCharDeviceBase_t
 * @return u8 : return the status of the init, using for upper level for checking
 */
u8 device_base_init(IMX6ULLCharDeviceBase_t* ptr_base_type, IMX6ULLCharInit_t* init_type);

/**
 * @brief this kind of init requires the handle placed
 * statically, calling this for destroying a base type
 * 
 * @param ptr_base_type: stack placed ptr of IMX6ULLCharDeviceBase_t
 * @return u8 : return the status of the init, using for upper level for checking
 */
void device_base_deinit(IMX6ULLCharDeviceBase_t* ptr_base_type);

/**
 * @brief This functions wrapped the major fetch of the device
 * 
 * @param base_type 
 * @return u16: result
 */
u16 device_major_number(IMX6ULLCharDeviceBase_t* base_type);

/**
 * @brief This functions wrapped the minor fetch of the device
 * 
 * @param base_type 
 * @return u16: result
 */
u16 device_minor_number(IMX6ULLCharDeviceBase_t* base_type);

#endif
