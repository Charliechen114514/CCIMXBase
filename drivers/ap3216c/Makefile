KER_DIR := /home/charliechen/imx6ull/linux-imx
RTFS_MODULE_TEST_PATH := ~/imx6ull/nfs/rootfs/module_test/
CURRENTDIR := $(shell pwd)
MODULE_NAME	:= ap3216c
obj-m += ${MODULE_NAME}.o
${MODULE_NAME}-objs := plt_${MODULE_NAME}.o driver_base.o

.PHONY: application device clean all upload

device:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KER_DIR) M=$(CURRENTDIR) modules

application:
	arm-linux-gnueabihf-gcc ${MODULE_NAME}_application.c -o ${MODULE_NAME}_application

all:
	make device;make application

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KER_DIR) M=$(CURRENTDIR) clean
	rm -f ${MODULE_NAME}_application

upload:
	cp ${MODULE_NAME}_application $(RTFS_MODULE_TEST_PATH)
	cp $(MODULE_NAME).ko $(RTFS_MODULE_TEST_PATH)