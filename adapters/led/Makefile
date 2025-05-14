CROSS_COMPILE := arm-linux-gnueabihf-

.PHONY: test

test:
	${CROSS_COMPILE}g++ led_test.cpp led_adapter.cpp -o led_test

install:
	sudo cp led_test ~/imx6ull/nfs/rootfs/home/charliechen/adapter_test

clean:
	rm -f led_test



