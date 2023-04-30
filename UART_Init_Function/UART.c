#include "stm32f10x.h"
#include <stdint.h>
#include "UART.h"

uint32_t BaudRate_Calc(uint32_t BaudRate, uint32_t freq)
{
	uint32_t dec, final;
	uint32_t div = freq;
	double frac = (double)div;
	double frac2 = 1.00;
	div = div/(BaudRate*16);
	frac = 16.00*(frac / ((double)(BaudRate*16)) - div);
	dec = (uint32_t)frac;
	frac2 = 100 *(frac - dec);
	if(frac2>50)
	{
		dec ++;
		if(dec == 16)
		{
			dec = 0;
			div ++;
		}
	}
	
	final = (div<<4);
	final+= dec;
	
	return final;
	
}



void UART_Init(uint8_t USART, uint32_t BaudRate)
{
	// Enable the alternate functions for pins
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	if(USART == 1)
	{
		// Enable GPIOA clock
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		// Enable UASRT1 Clock
		RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
		// Reset PA9 and PA10
		GPIOA->CRH &= ~(GPIO_CRH_CNF9 | GPIO_CRH_CNF10);
		GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_MODE10);
		
		// Set PA9 as Alternate function 50MHz Output pushpull
		GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);		// output (TX)
		
		// Set PA10 as input pulldown
		GPIOA->CRH |= (GPIO_CRH_CNF10_1);	// input (RX)
		
		uint32_t br = BaudRate_Calc(BaudRate, 72000000);
		
		// Set Baud Rate
		USART1->BRR = br;
		
		// enable UASRT
		USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
	}
	
	else if(USART == 2)
	{
		// Enable GPIOA clock
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

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
	uint32_t br = BaudRate_Calc(BaudRate, 36000000);
	USART2->BRR = br;
	
	// enable UASRT
	USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
	}
	
	else{ // USART 3
		// Enable GPIOB clock
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

		// Enable UASRT3 Clock
		RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
		
		// Reset PB10 and PB11
		GPIOB->CRL &= ~(GPIO_CRH_CNF11 | GPIO_CRH_CNF10);
		GPIOB->CRL &= ~(GPIO_CRH_MODE11| GPIO_CRH_MODE10);
		
		// Set PB10 as Alternate function 50MHz Output pushpull
		GPIOB->CRH |= (GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10);		// output (TX)
		// Set PB11 as input pulldown
		GPIOB->CRH |= (GPIO_CRH_CNF11_1);	// input (RX)
		
		// Set Baud Rate
		uint32_t br = BaudRate_Calc(BaudRate, 36000000);
		USART3->BRR = br;
		
		// enable UASRT
		USART3->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
	}
}






void transmit_char(uint8_t USART, uint8_t data)
{
	
	if(USART == 1)
	{
		while((USART1->SR & USART_SR_TC) == 0); // wait until previous data is sent
		// load data register with the byte to be sent
		USART1->DR = data;
	}
	else if(USART == 2)
	{
		while((USART2->SR & USART_SR_TC) == 0); // wait until previous data is sent
		// load data register with the byte to be sent
		USART2->DR = data;
	}
	else
	{
		while((USART3->SR & USART_SR_TC) == 0); // wait until previous data is sent
		// load data register with the byte to be sent
		USART3->DR = data;
	}
}


void transmit_string(uint8_t USART, uint8_t* data, uint16_t length)
{
	
	int i;
	for(i=0; i<length; i++)
	{
		transmit_char(USART, data[i]);
	}
	transmit_char(USART, '\n');
	
	
}