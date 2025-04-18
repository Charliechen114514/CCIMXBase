#include "driver_base.h"
static u8 _alloc_chardev_region(
        IMX6ULLCharDeviceBase_t* ptr_base_type, 
        IMX6ULLCharInit_t* init_type)
{
    int process_cached = 0;
    pr_info("\r\nRequesting the CharDev Region!\r\n ");
    if(init_type->led_dev_major)
    {
        pr_info("We have already the major number, passing as: %d!\r\n", init_type->led_dev_major);
        ptr_base_type->device_id = MKDEV(init_type->led_dev_major, 0);
        process_cached = register_chrdev_region(ptr_base_type->device_id, init_type->dev_cnt, init_type->name_ptr);
    }
    else
    {
        /* or, we need kernel allocate the dev number */
        pr_info("As no dev number specified, query the kernel!\r\n");
        process_cached = alloc_chrdev_region(&ptr_base_type->device_id, 0, init_type->dev_cnt, init_type->name_ptr);
    }

    // failed!
    return process_cached >= 0;
}

static u8 
_init_cdev( IMX6ULLCharDeviceBase_t* ptr_base_type, 
            IMX6ULLCharInit_t* init_type)
{
    int process_cached = 0;
    pr_info("Registering the CharDev handle!\r\n ");
    cdev_init(&ptr_base_type->char_device, init_type->device_operations);
    process_cached = cdev_add(
        &ptr_base_type->char_device, 
        ptr_base_type->device_id, 
        ptr_base_type->device_count);
    return process_cached >= 0;
}

static u8 _create_chardev_class(IMX6ULLCharDeviceBase_t* ptr_base_type, IMX6ULLCharInit_t* init_type)
{
    int process_cached = 0;
    pr_info("About to create class files for chardev: %s", init_type->name_ptr);
    ptr_base_type->device_class = class_create(init_type->name_ptr);
    if(IS_ERR(ptr_base_type->device_class))
    {
        pr_err("Occurring errors in creating class! with num: %ld", PTR_ERR(ptr_base_type->device_class));
        process_cached = PTR_ERR(ptr_base_type->device_class);
    }
    return process_cached >= 0;
}

static u8 _create_device(IMX6ULLCharDeviceBase_t* ptr_base_type, IMX6ULLCharInit_t* init_type)
{
    int process_cached = 0;
    pr_info("About to create device files for chardev: %s", init_type->name_ptr);
    ptr_base_type->ker_device_handle = device_create(ptr_base_type->device_class, NULL, ptr_base_type->device_id, NULL, init_type->name_ptr);
    if(IS_ERR(ptr_base_type->ker_device_handle))
    {
        pr_err("Occurring errors in creating class! with num: %ld", PTR_ERR(ptr_base_type->ker_device_handle));
        process_cached = PTR_ERR(ptr_base_type->ker_device_handle);
    }
    return process_cached >= 0;
}

u8 device_base_init(IMX6ULLCharDeviceBase_t* ptr_base_type, IMX6ULLCharInit_t* init_type)
{
    /* for the first, we need to allocate the device id for regions*/
    ptr_base_type->device_count = init_type->dev_cnt;
    if(!_alloc_chardev_region(ptr_base_type, init_type)){
        pr_err("Failed to register char device regions\r\n");
        goto _device_base_handle_failed_register_chardev_region;
    }else{
        pr_info("Successfully finish chardev region init!\r\n");
    }

    ptr_base_type->char_device.owner = THIS_MODULE;

    if(!_init_cdev(ptr_base_type, init_type)){
        pr_err("Failed to add char dev into kernel!\r\n");
        goto _device_base_handle_error_addchdev;
    }else{
        pr_info("Successfully finish chardev add!\r\n");
    }

    if(!_create_chardev_class(ptr_base_type, init_type)){
        pr_err("Failed to create class in kernel!\r\n");
        goto _device_base_handle_error_create_class;
    }else{
        pr_info("Successfully create class\r\n");
    }

    if(!_create_device(ptr_base_type, init_type)){
        pr_err("Failed to create device in kernel!\r\n");
        goto _device_base_handle_error_create_device;
    }else{
        pr_info("Successfully create device\r\n");
    }
    pr_info("Init the base type done!\r\n");
    return 1;
_device_base_handle_error_create_device:
    class_destroy(ptr_base_type->device_class);
_device_base_handle_error_create_class:
    cdev_del(&ptr_base_type->char_device);
_device_base_handle_error_addchdev:
    unregister_chrdev_region(ptr_base_type->device_id, init_type->dev_cnt);
_device_base_handle_failed_register_chardev_region:
    pr_err("init issue quits!\r\n");
    return 0;
}

void device_base_deinit(IMX6ULLCharDeviceBase_t* ptr_base_type)
{
    pr_info("Start deinit the device!\r\n");
    pr_info("Destroy the kernel device!\r\n");
    device_destroy(ptr_base_type->device_class, ptr_base_type->device_id);
    pr_info("Destror the kernel class!\r\n");
    class_destroy(ptr_base_type->device_class);
    pr_info("Destroy the char dev raw handle\r\n");
    cdev_del(&ptr_base_type->char_device);
    pr_info("unregistering the chardev region!\r\n");
    unregister_chrdev_region(ptr_base_type->device_id, ptr_base_type->device_count);
    pr_info("deinit the device issue done!\r\n");
}

u16 device_major_number(IMX6ULLCharDeviceBase_t* base_type)
{
    return MAJOR(base_type->device_id);
}

u16 device_minor_number(IMX6ULLCharDeviceBase_t* base_type)
{
    return MINOR(base_type->device_id);
}



