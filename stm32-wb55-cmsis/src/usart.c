#include "usart.h"

#include <stdint.h>

#define STM32WB55xx

#include "stm32wbxx.h"

#define BIT(i) (1UL << (i))


void usart_init(uint32_t baud) {
    GPIO_TypeDef* gpio = GPIOB;

    RCC->APB2ENR |= BIT(14);

    uint32_t af = 7;

    uint32_t tx = 6;
    uint32_t rx = 7;

    gpio->OTYPER |= BIT(rx);
    gpio->OSPEEDR &= ~((3UL << 2 * rx) | (3UL << 2 * tx));
    gpio->OSPEEDR |= (1UL << 2 * rx) | (1UL << 2 * tx);

    gpio->PUPDR &= ~((3UL << 2 * rx) | (3UL << 2 * tx));
    gpio->PUPDR |= (1UL << 2 * rx) | (1UL << 2 * tx);

    gpio->MODER &= ~((3UL << 2 * rx) | (3UL << 2 * tx));
    gpio->MODER |= (2UL << 2 * rx) | (2UL << 2 * tx);

    gpio->AFR[rx / 8] &= ~(15UL << 4 * (rx % 8));
    gpio->AFR[rx / 8] |= af << 4 * (rx % 8);

    gpio->AFR[tx / 8] &= ~(15UL << 4 * (tx % 8));
    gpio->AFR[tx / 8] |= af << 4 * (tx % 8);

    USART1->CR1 = 0;

    USART1->CR1 |= BIT(2) | BIT(5);

    uint32_t usartdiv = 4000000 / baud;
    USART1->BRR = usartdiv;

    USART1->CR1 |= BIT(0);
}
