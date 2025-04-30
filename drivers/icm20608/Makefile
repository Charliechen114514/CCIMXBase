KER_DIR := /home/charliechen/imx6ull/linux-imx
RTFS_MODULE_TEST_PATH := ~/imx6ull/nfs/rootfs/module_test/
CURRENTDIR := $(shell pwd)
MODULE_NAME	:= icm20608
ADAPTER_NAME := icm20608_adapter
obj-m += ${MODULE_NAME}.o
${MODULE_NAME}-objs := plt_${MODULE_NAME}.o driver_base.o

.PHONY: application device clean all upload

device:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KER_DIR) M=$(CURRENTDIR) modules

application:
	arm-linux-gnueabihf-gcc ${MODULE_NAME}_application.c -o ${MODULE_NAME}_application
	arm-linux-gnueabihf-g++ ${ADAPTER_NAME}.cpp adapter_test.cpp -o adapter_test
all:
	make device;make application

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KER_DIR) M=$(CURRENTDIR) clean
	rm -f ${MODULE_NAME}_application
	rm -f adapter_test

upload:
	cp ${MODULE_NAME}_application $(RTFS_MODULE_TEST_PATH)
	cp $(MODULE_NAME).ko $(RTFS_MODULE_TEST_PATH)
	cp adapter_test $(RTFS_MODULE_TEST_PATH)