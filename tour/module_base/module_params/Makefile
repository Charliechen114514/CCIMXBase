KDIR := ~/imx6ull/linux-imx
RT_FS := ~/imx6ull/nfs/rootfs/home/charliechen/module_test
module_name := module_params
obj-m := ${module_name}.o

module_build:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) modules

clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C ${KDIR} M=$(shell pwd) clean

install:
	sudo cp ${module_name}.ko ${RT_FS}

