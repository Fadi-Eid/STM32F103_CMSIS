#ifndef UART_H
#define UART_H

#include <stdint.h>

void UART_Init(uint8_t USART, uint32_t BaudRate);
uint32_t BaudRate_Calc(uint32_t BaudRate, uint32_t freq);
void transmit_char(uint8_t USART, uint8_t data);
void transmit_string(uint8_t USART, uint8_t* data, uint16_t length);

#endif