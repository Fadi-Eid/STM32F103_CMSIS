#include "stm32f10x.h"
#include <string.h>

void UART2_Init(void);
void transmit_char(uint8_t data);
void transmit_string(uint8_t* data, uint16_t length);


int main(void)
{
	UART2_Init();
	uint8_t string[] = "Hello from stm32";
	
	while(1)
	{
		transmit_string(string, strlen(string));
	}
	
	
}

void transmit_string(uint8_t* data, uint16_t length)
{
	int i;
	for(i=0; i<length; i++)
	{
		transmit_char(data[i]);
	}
	transmit_char('\n');
}

void transmit_char(uint8_t data)
{
	while((USART2->SR & USART_SR_TXE) == 0); // wait until previous data is sent
		// load data register with the byte to be sent
		USART2->DR = data;
}


void UART2_Init(void)
{
// Enable GPIOA clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Enable the alternate functions for pins
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Enable UASRT2 Clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	// Reset PA2 and PA3
	GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_CNF2);
	GPIOA->CRL &= ~(GPIO_CRL_MODE3 | GPIO_CRL_MODE2);
	
	// Set PA2 as Alternate function 50MHz Output pushpull
	GPIOA->CRL |= (GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2);		// output (TX)
	
	// Set PA3 as input pulldown
	GPIOA->CRL |= (GPIO_CRL_CNF3_1);	// input (RX)
	
	// Set Baud Rate
	USART2->BRR = 0xEA6; 		//9600
	
	// enable UASRT
	USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}

