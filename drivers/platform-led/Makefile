KDIR := /home/charliechen/imx6ull/linux-imx
CURRENTDIR := $(shell pwd)
RTFS_MODULE_TEST_PATH := ~/imx6ull/nfs/rootfs/module_test/
MODULE_NAME := plt_charliesled
APP_NAME := chrdev_application
ADAPTER_TEST_NAME := led_test_adapter
obj-m := $(MODULE_NAME).o
$(MODULE_NAME)-objs := led.o  driver_base.o 

.PHONY: char_dev clean application all

char_dev:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KDIR) M=$(CURRENTDIR) modules

application:
	arm-linux-gnueabihf-gcc ${APP_NAME}.c -o ${APP_NAME}

adapter_test:
	arm-linux-gnueabihf-g++ led_app_adapter.cpp ${ADAPTER_TEST_NAME}.cpp -o ${ADAPTER_TEST_NAME}

all:
	make char_dev;make application;make adapter_test

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KDIR) M=$(CURRENTDIR) clean
	rm -f ${APP_NAME}
	rm -f ${ADAPTER_TEST_NAME}

upload:
	cp ${APP_NAME} $(RTFS_MODULE_TEST_PATH)
	cp ${ADAPTER_TEST_NAME} $(RTFS_MODULE_TEST_PATH)
	cp $(MODULE_NAME).ko $(RTFS_MODULE_TEST_PATH)
