#include "stm32f10x.h"
#include <stdint.h>


/* initialize systick timer */
void systick_init(void);
/*	Delay function that utilizes Systick timer	*/
void delay_ms(uint32_t time_ms);
/*	Delay 1ms function	*/
void delayMillis(void);



int main(void)
{
	// blink LED each 12 seconds
	uint32_t time = 12000;
	
	/* configure PC13 as Output PushPull*/
	// enable clock for APB2 bus
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
	GPIOC->CRH |= (GPIO_CRH_MODE13_0);
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);		// pushpull mode
	
	while(1)
	{
		// output logic 1 on PC13
		GPIOC->ODR |= GPIO_ODR_ODR13;
		// delay 
		delay_ms(time);
		// output logic 0 on PC13
		GPIOC->ODR &= ~(GPIO_ODR_ODR13);
		// delay
		delay_ms(time);
	}

}




void systick_init(void)
{
	SysTick->CTRL = 0x00;					// reset all bits (inactivate)
	SysTick->LOAD = 0x00FFFFFF;		// load to max value
	SysTick->VAL = 0;		// initialize with value 0
	
	/*	Enable systick	*/
	SysTick->CTRL |= SysTick_CTRL_ENABLE;			// enable systick timer
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;	// set clock source to AHB (same as the MPU --> 72MHz)
}

void delayMillis(void)
{
	// load the systick LOAD register
	SysTick->LOAD = (72000-1);	// 72k cycles = 1ms
	SysTick->VAL = 0x00;
	
	
		while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0);

}

void delay_ms(uint32_t time_ms)
{
	systick_init();
	for(;time_ms>0; time_ms--)
	{
		delayMillis();
	}
	return;
}
