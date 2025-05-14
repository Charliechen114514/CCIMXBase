KDIR := ~/imx6ull/linux-imx
RT_FS := ~/imx6ull/nfs/rootfs/home/charliechen/module_test
module_name := sys_info
obj-m := ${module_name}.o
.PHONY: clean module_build install

module_build:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) clean

install:
	sudo cp ${module_name}.ko ${RT_FS}

