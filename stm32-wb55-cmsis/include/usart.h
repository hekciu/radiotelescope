#ifndef USART_H
#define USART_H

#include <stdint.h>


void usart_init(uint32_t baud);
void usart_transmit(const char* buffer);

#endif
