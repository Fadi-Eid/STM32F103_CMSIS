#include "stm32f10x.h"
#include "stdint.h"

// global variable for the interrupt
volatile uint8_t signal = 0;

void delay1(void);
void delay2(void);


int main(void)
{
	/* configure PC13 as Output PushPull*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // enable clock for APB2 bus
	GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13); // rest mode and config
	GPIOC->CRH |= (GPIO_CRH_MODE13_0);		// mode output 10MHZ
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);		// pushpull mode
	
	
	/* Configure PB5 as input pullup*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~(GPIO_CRL_MODE5 | GPIO_CRL_CNF5); // reset to all zeros
	GPIOB->CRL &= ~(GPIO_CRL_MODE5);	// input
	GPIOB->CRL |= (GPIO_CRL_CNF5_1);	// pullup/pulldown
	GPIOB->ODR |= GPIO_ODR_ODR5;			// pullup
	
	// disable interrupts
	__disable_irq();
	
	// enable RCC for AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;  // Enable AFIO CLOCK
	
	// configure PB5 as External interrupt
	AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI5_PB;
	
	// unmask line 5-9 
	EXTI->IMR |= EXTI_IMR_MR5;
	
	// select falling trigger
	EXTI->FTSR |= EXTI_FTSR_TR5;
	
	// set priority of interrupt line 9_5
	NVIC_SetPriority (EXTI9_5_IRQn, 1);  // Set Priority to 1
	
	// enable external interrupt from line 5-9
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	// re-enable irq
	__enable_irq();
	
	
	while(1)
	{
		if(signal == 1) // blink slow
		{
			// output logic 1 on PC13
				GPIOC->ODR |= GPIO_ODR_ODR13;
				// delay 
				delay1();
				// output logic 0 on PC13
				GPIOC->ODR &= ~(GPIO_ODR_ODR13);
				// delay
				delay1();
		}
		else // blink fast
		{
			// output logic 1 on PC13
				GPIOC->ODR |= GPIO_ODR_ODR13;
				// delay 
				delay2();
				// output logic 0 on PC13
				GPIOC->ODR &= ~(GPIO_ODR_ODR13);
				// delay
				delay2();
		}
	}
	
}


// IRQ Handler
void EXTI9_5_IRQHandler()
{
		if (EXTI->PR & EXTI_PR_PR5)    // If the PB5 triggered the interrupt
	{
		if(signal == 0) signal = 1;
		else signal = 0;
		EXTI->PR |= EXTI_PR_PR5;  // Clear the interrupt flag by writing a 1 
	}
}


// delay functions
void delay1(void)
{
	int i, j;
	for(i=0; i<100000; i++){
		for(j=0; j<4; j++){}
	}
}

void delay2(void)
{
	int i, j;
	for(i=0; i<100000; i++){
		for(j=0; j<2; j++){}
	}
}