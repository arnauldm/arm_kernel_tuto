
Retreiving u-boot sources

	git clone git://git.denx.de/u-boot.git

Compiling u-boot for versatile express on cortex-a9
(http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.subset.boards.express/index.html)

	ARCH=arm CROSS_COMPILE=arm-none-eabi- make vexpress_ca9x4_defconfig
	ARCH=arm CROSS_COMPILE=arm-none-eabi- make 

Running the u-boot binary on QEMU 

	qemu-system-arm -M vexpress-a9 -m 512M -serial stdio -kernel u-boot 

