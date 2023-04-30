#include "systick_time.h"
#include "lcd_1602.h"

/*
I2C2
PB10 -> SCL
PB11 -> SDA

I2C1
PB6 -> SCL
PB7 -> SDA
*/



int main(void)
{
		systick_init();// initialize the delay function (Must initialize)
		lcd_i2c_init(2);
		lcd_i2c_msg(2, 1, 0,"Welcome to: ");
		lcd_i2c_msg(2, 2, 6,"STM32");
	while(1);
	
}
