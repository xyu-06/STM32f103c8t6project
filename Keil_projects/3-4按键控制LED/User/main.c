#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"

int main (void)
{
	
	LED_Init();
	Key_Init();
	

	while (1)
	{
		uint8_t numble;
		numble=KeyValue();
		if(numble==1)
		{
		LEDA0_Turn();
		}
		else if (numble==2)
		{
		LEDA1_Turn();
		}
	}
}
