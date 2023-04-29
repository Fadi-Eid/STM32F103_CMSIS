#include "stm32f10x.h"
#include <stdint.h>

/* initialize systick timer  timer */
void systick_interrupt_init(uint32_t time);


int main(void)
{
	/* configure PC13 as Output PushPull*/
	// enable clock for APB2 bus
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= (GPIO_CRH_MODE13_0);
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);		// pushpull mode
	
	
	systick_interrupt_init(200);	// called once, will run until disabled
	
	while(1);
}


void systick_interrupt_init(uint32_t time) // max = 233ms
{
	if(time<=(233))
	{
		__disable_irq();
		SysTick->CTRL = 0x00;										// reset
		SysTick->LOAD = (uint32_t)(time * 72000);
		SysTick->VAL = 0x00;										// initialize
		SysTick->CTRL |= (SysTick_CTRL_TICKINT|SysTick_CTRL_ENABLE|SysTick_CTRL_CLKSOURCE);	// enable the interrupt
		__enable_irq();
	}
}



/*	Systick interrupt Handler	*/
void SysTick_Handler(void)	// will reload LOAD register and reset the timer
{
	// toggle gpio PC13
	if((GPIOC->ODR & GPIO_ODR_ODR13) == 0)
	{
		GPIOC->ODR |= GPIO_ODR_ODR13;
	}
	else{
		GPIOC->ODR &= ~(GPIO_ODR_ODR13);
	}
}
