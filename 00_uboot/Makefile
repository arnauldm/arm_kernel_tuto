
all: u-boot/u-boot

u-boot/u-boot:
	make -C u-boot vexpress_ca9x4_defconfig ARCH=arm CROSS_COMPILE=arm-none-eabi- 
	make -C u-boot ARCH=arm CROSS_COMPILE=arm-none-eabi- 

run: u-boot/u-boot
	qemu-system-arm -M vexpress-a9 -m 512M -serial stdio -kernel $^

clean:
	make -C u-boot clean
