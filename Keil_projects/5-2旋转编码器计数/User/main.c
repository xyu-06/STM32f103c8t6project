#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encode.h"
int main (void)
{
	OLED_Init();
	Encode_Init();
	while (1)  
	{
		OLED_ShowSignedNum(1,1,Encode_Get(),4);
	}
}
