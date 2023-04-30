#include "stm32f10x.h"
#include <stdint.h>
#include <string.h>
#include "uart_rx_int.h"
#include <stdio.h>

volatile uint8_t signal = 1;

int main(void)
{
	
	
	/* configure PC13 as Output PushPull*/
	// enable clock for APB2 bus
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= (GPIO_CRH_MODE13_0);
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);		// pushpull mode
	
	UART_Init_Interrupt_Receive(2, 9600);
	
	uint8_t string[] = "Hello from stm32";
	uint16_t i = 0;
	
	for(i=0; i<10; i++)
	{
		transmit_string(2, string, strlen(string));
	}
	

	
	while(1)
	{
		if(signal == 1)
		{
			// output logic 1 on PC13
			GPIOC->ODR |= GPIO_ODR_ODR13;
		}
		else
		{
			GPIOC->ODR &= ~(GPIO_ODR_ODR13);
		}
	}
	
}

void USART2_IRQHandler()
{
	
	if(USART2->SR & USART_SR_ORE)
	{
			// process overrun error if needed
	}
	
  if(USART2->SR & USART_SR_RXNE)
  {
		uint8_t data = receive_char(2);
		
		if(data != '\n' && data != '\r' && data != '\0')
		{
			if(signal==1) 
			signal = 2;
			else 
				signal = 1;
			
			uint8_t msg[] = "received";
			transmit_string(2, msg, 8);
			transmit_char(2, data);
		}
    
		
  }
}