CMSIS_CORE_INCLUDE=cmsis/cmsis_core/CMSIS/Core/Include
CMSIS_WB_INCLUDE=cmsis/cmsis_wb/Include
HEADERS_INCLUDE=include

SRC_DIR=src

#TODO: add headers to dependencies

main.o: main.c
	arm-none-eabi-gcc -I${CMSIS_CORE_INCLUDE} -I${CMSIS_WB_INCLUDE} -I${HEADERS_INCLUDE} -mcpu=cortex-m4 main.c -c -o main.o

usart.o: ${SRC_DIR}/usart.c
	arm-none-eabi-gcc -I${CMSIS_CORE_INCLUDE} -I${CMSIS_WB_INCLUDE} -I${HEADERS_INCLUDE} -mcpu=cortex-m4 ${SRC_DIR}/usart.c -c -o usart.o

led.o: ${SRC_DIR}/led.c
	arm-none-eabi-gcc -I${CMSIS_CORE_INCLUDE} -I${CMSIS_WB_INCLUDE} -I${HEADERS_INCLUDE} -mcpu=cortex-m4 ${SRC_DIR}/led.c -c -o led.o

firmware.elf: main.o usart.o led.o
	arm-none-eabi-gcc -T link.ld -nostdlib main.o usart.o led.o -o firmware.elf

firmware.bin: firmware.elf
	arm-none-eabi-objcopy -O binary firmware.elf firmware.bin

firmware.s: main.c
	arm-none-eabi-gcc -mcpu=cortex-m4 main.c -S -o firmware.s

.PHONY: build flash clean assembly

build: firmware.bin

assembly: firmware.s

flash:
	st-flash --reset write firmware.bin 0x8000000

clean:
	rm -f -- *.o firmware.elf firmware.bin firmware.s
