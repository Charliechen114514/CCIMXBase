KDIR := ~/imx6ull/linux-imx
RT_FS := ~/imx6ull/nfs/rootfs/home/charliechen/module_test
module_name := module_stacking
obj-m := ${module_name}_usr.o
obj-m += ${module_name}_lib.o
.PHONY: clean module_build install

module_build:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) clean

install:
	sudo cp ${module_name}_usr.ko ${RT_FS}
	sudo cp ${module_name}_lib.ko ${RT_FS}

