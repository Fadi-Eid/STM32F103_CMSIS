#include "stm32f10x.h"
#include "i2c.h"

#define I2C_FASTMODE 0x2D
#define I2C_STDMODE 0xB4

uint8_t data[2] = {0x00, 0xFF};

int main(void)
{
	I2C_Init(2);		// initialize I2C 2
	
	while(1)
	{
		I2C_Write(2, 0x27, data, 2);		// I2C2, device address is D0, 2 bytes of data
	}
}