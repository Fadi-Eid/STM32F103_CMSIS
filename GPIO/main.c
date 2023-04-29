// register level manipulation of GPIO Output implementation
#include "stm32f10x.h"

void delay(void);


int main(void)
{
	/* configure PC13 as Output PushPull*/
	// enable clock for APB2 bus
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= (GPIO_CRH_MODE13_0);
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);		// pushpull mode
	
	/* Configure PB5 as input pullup*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5); // reset to all zeros
	GPIOB->CRL &= ~(GPIO_CRL_MODE5);	// input
	GPIOB->CRL |= (GPIO_CRL_CNF5_1);	// pullup/pulldown
	GPIOB->ODR |= GPIO_ODR_ODR5;			// pullup
	
	// data to store button value
	uint32_t button;
	int i;
	
	while(1)
	{
		// read logic level on PB5
		button = GPIOB->IDR;
		
		if((button&GPIO_IDR_IDR5)== 0) // button pressed
		{
			for(i=0; i<10; i++)
			{
				// output logic 1 on PC13
				GPIOC->ODR |= GPIO_ODR_ODR13;
				// delay 
				delay();
				// output logic 0 on PC13
				GPIOC->ODR &= ~(GPIO_ODR_ODR13);
				// delay
				delay();
			}
			
		}
		
	}
	
}

// delay function
void delay(void)
{
	int i, j;
	for(i=0; i<100000; i++){
		for(j=0; j<4; j++){}
	}
}