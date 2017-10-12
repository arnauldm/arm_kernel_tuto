
CFLAGS 	= -Os -Wall -Wextra -Wconversion -ffreestanding
BUILD   = ../build/task0

all: $(BUILD) $(BUILD)/task0.bin 

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/task0.bin: $(BUILD)/task0.elf
	arm-none-eabi-objcopy -O binary $^ $@ 

$(BUILD)/task0.elf: $(BUILD)/task0.o 
	arm-none-eabi-gcc $^ -nostdlib -lgcc  -T link.ld -o $@

$(BUILD)/%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-a9 -c -o $@ $^

clean:
	rm -f *~ $(BUILD)/*.o $(BUILD)/task0.elf $(BUILD)/task0.bin

disas: $(BUILD)/task0.bin
	arm-none-eabi-objdump -b binary -m arm -D $^
