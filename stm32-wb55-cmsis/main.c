#include <stdbool.h>

#define STM32WB55xx
#include "stm32wbxx.h"

#include "common.h"
#include "usart.h"
#include "led.h"



void spin(uint32_t i) { while(i > 0) i--; };

__attribute__((interrupt("IRQ")))
void usart1_irq_handler(void) {
    if (IS_FLAG_SET(USART1->ISR, 5)) {
        blink_green_led();

        uint8_t byte = USART1->RDR & 255;
    }
}


__attribute__((naked, noreturn)) void _reset(void) {
    setup_green_led();
    usart_init(115200);

    NVIC_EnableIRQ(USART1_IRQn);

    while(true) {
        usart_transmit("dupa\r\n");

        blink_green_led();

        spin(99999);
    };
}

extern void _estack(void);  // Defined in link.ld

// 16 standard and 63 STM32WB55-specific handlers
__attribute__((section(".vectors"))) void (*const tab[16 + 63])(void) = {
  _estack, _reset, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, usart1_irq_handler, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

