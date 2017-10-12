
MCPU 	= cortex-a9
BOARD 	= vexpress-a9

ASFLAGS	= -g 
CFLAGS 	= -g -Wall -Wextra -Wconversion -ffreestanding
LDFLAGS = -nostdlib -lgcc 

C_SRC = $(wildcard *.c)
C_INC = $(wildcard *.h)
C_OBJ = $(patsubst %.c, $(BUILD)/%.o, $(C_SRC))


BUILD   = build/kernel

all: $(BUILD) $(BUILD)/kernel.elf 

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/kernel.elf: $(BUILD)/startup.o $(C_OBJ) $(BUILD)/task0.o
	arm-none-eabi-gcc $^ $(LDFLAGS) -T link.ld -o $@ 

$(BUILD)/task0.o: build/task0/task0.bin
	arm-none-eabi-objcopy -I binary $^ -B arm -O elf32-littlearm --rename-section .data=.task0 $@

build/task0/task0.bin:
	make -C task0

$(BUILD)/startup.o: startup.S
	arm-none-eabi-as $(ASFLAGS) -mcpu=$(MCPU) -o $@ $^

$(BUILD)/%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -mcpu=$(MCPU) -c -o $@ $^

run: $(BUILD)/kernel.elf
	QEMU_AUDIO_DRV=none qemu-system-arm -M $(BOARD) -m 128M -serial stdio -kernel $^

clean:
	rm -f *~ $(BUILD)/*.o $(BUILD)/kernel.elf 
	make -C task0 clean

indent:
	indent -kr -nut -pcs *.c *.h

