
MCPU 	= cortex-a9
BOARD 	= vexpress-a9

ASFLAGS	= -g 
CFLAGS 	= -g -Wall -Wextra -Wconversion -ffreestanding
LDFLAGS = -nostdlib -lgcc 

C_SRC = $(wildcard *.c)
C_INC = $(wildcard *.h)
C_OBJ = $(patsubst %.c, $(BUILD)/%.o, $(C_SRC))


BUILD   = build

all: $(BUILD) $(BUILD)/main.elf

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/main.elf: $(BUILD)/startup.o $(C_OBJ)
	arm-none-eabi-gcc $^ $(LDFLAGS) -T link.ld -o $@ 

$(BUILD)/startup.o: startup.S
	arm-none-eabi-as $(ASFLAGS) -mcpu=$(MCPU) -o $@ $^

$(BUILD)/%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -mcpu=$(MCPU) -c -o $@ $^

run: $(BUILD)/main.elf
	QEMU_AUDIO_DRV=none qemu-system-arm -M $(BOARD) -m 128M -serial stdio -kernel $^

clean:
	rm -f *~ $(BUILD)/*.o $(BUILD)/main.elf 

indent:
	indent -kr -nut -pcs *.c *.h

