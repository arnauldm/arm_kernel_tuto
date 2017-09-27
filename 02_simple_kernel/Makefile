
MCPU 	= cortex-a9
BOARD 	= vexpress-a9

ASFLAGS	= -g 
CFLAGS 	= -g -Wall -Wextra -ffreestanding
LDFLAGS = -nostdlib -lgcc 

all: main.elf

main.elf: startup.o lib.o uart.o main.o 
	arm-none-eabi-gcc $^ $(LDFLAGS) -T link.ld -o $@ 

startup.o: startup.S
	arm-none-eabi-as $(ASFLAGS) -mcpu=$(MCPU) -o $@ $^

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -mcpu=$(MCPU) -c -o $@ $^

run: main.elf
	QEMU_AUDIO_DRV=none qemu-system-arm -M $(BOARD) -m 128M -serial stdio -kernel $^

clean:
	rm -f *~ *.o main.elf 

indent:
	indent -kr -nut -pcs *.c *.h

