CROSS_COMPILE := arm-linux-gnueabihf-

.PHONY: test

test:
	${CROSS_COMPILE}g++ ap3216c_test.cpp ap3216c_adapter.cpp -o ap3216c_test

install:
	sudo cp ap3216c_test ~/imx6ull/nfs/rootfs/home/charliechen/adapter_test

clean:
	rm -f ap3216c_test