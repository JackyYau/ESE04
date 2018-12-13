CROSS-COMPILER = arm-none-eabi-

all: homework.bin

homework.bin: homework.c isr_vectors.s
	$(CROSS-COMPILER)gcc -Wall -mcpu=cortex-m4 -mthumb -nostartfiles -T stm32f4.ld homework.c isr_vectors.s -o homework.elf
	$(CROSS-COMPILER)objcopy -O binary homework.elf homework.bin

flash:
	sudo st-flash --reset write homework.bin 0x8000000

clean:
	rm -f *.o *.elf *.bin
