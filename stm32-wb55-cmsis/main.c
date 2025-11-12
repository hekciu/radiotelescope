#include <stdbool.h>

#define STM32WB55xx

#include "stm32wbxx.h"

#include "usart.h"

#define BIT(i) (1UL << (i))

static bool led_on = false;


static inline void setup_green_led() {
    RCC->AHB2ENR |= BIT(1);

    GPIOB->MODER &= ~(3UL << 2 * 0);
    GPIOB->MODER |= 1UL << 2 * 0;
}


void blink_green_led(void) {
    if (led_on) {
        led_on = false;

        GPIOB->BSRR &= ~BIT(0);
        GPIOB->BSRR |= BIT(16);
    } else {
        led_on = true;

        GPIOB->BSRR &= ~BIT(16);
        GPIOB->BSRR |= BIT(0);
    }
}


__attribute__((interrupt("IRQ")))
void usart1_irq_handler(void) {
    if ((USART1->ISR & BIT(5)) >> 5 == 1) {
        blink_green_led();

        uint8_t byte = USART1->RDR & 255;
    }
}


__attribute__((naked, noreturn)) void _reset(void) {
    setup_green_led();
    usart_init(115200);

    NVIC_EnableIRQ(USART1_IRQn);

    while(true) {};
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

