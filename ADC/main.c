#include "stm32f10x.h"
#include "ADC.h"
#include "string_function.h"
#include "lcd_1602.h"

char num[10];
int analog_rx = 0;
int main(void)
{
// Initialize the ADC
	systick_init();
	adc_init(adc1, PA, 0);
	
	// initialize LCD
	lcd_i2c_init(2);
	lcd_i2c_msg(2, 1, 0,"ADC Reader ");
	DelayMs(1500);
	
	while(1)
	{
		if(adc_check(adc1, PA, 0))
		{
			analog_rx = adc_rx(adc1, PA, 0);
			//analog_rx = analog_rx;12341234
			
			int2char(analog_rx, num);
			
			// send to LCD
			lcd_i2c_msg(2, 1, 0,"                   ");
			lcd_i2c_msg(2, 1, 0, num);
			DelayMs(100);
			str_empty(num);
		}
	}
}