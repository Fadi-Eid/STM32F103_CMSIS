#include "stm32f10x.h"
#include <stdint.h>
#include <string.h>
#include "UART.h"

int main(void)
{
	UART_Init(2, 9600);
	uint8_t string[] = "Hello from stm32";
	
	
	while(1)
	{
		transmit_string(2, string, strlen(string));
	}
	
}