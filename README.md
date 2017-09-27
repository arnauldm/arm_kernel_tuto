
# Setting up ARM toolchain on GNU Linux / Debian

> sudo apt-get install qemu-system-arm 

> sudo apt-get install gcc-arm-none-eabi binutils-arm-none-eabi

To view a list of all supported processors for your target, use:

> mcpu=?

arm-none-eabi-as -mcpu=cortex-a9 -g startup.s -o startup.o
arm-none-eabi-gcc -mcpu=cortex-a9 -g -c main.c -o main.o
arm-none-eabi-ld -T link.ld startup.o main.o -o main.elf
arm-none-eabi-objcopy -O binary main.elf main.bin


> qemu-system-arm -M sabrelite -m 128M -nographic -kernel main.bin -d guest_errors

`-kernel` option loads a binary file (usually a Linux kernel) inside the system
memory starting at address 0x00010000
