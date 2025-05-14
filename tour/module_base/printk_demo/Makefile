KDIR := ~/imx6ull/linux-imx-debug
RT_FS := ~/imx6ull/nfs/rootfs/home/charliechen/module_test
module_name := printk_demo
obj-m := ${module_name}.o
ccflags-y += -DDEBUG
CFLAGS_printk_demo.o += -DDEBUG
.PHONY: clean module_build install

module_build:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) clean

install:
	sudo cp ${module_name}.ko ${RT_FS}

