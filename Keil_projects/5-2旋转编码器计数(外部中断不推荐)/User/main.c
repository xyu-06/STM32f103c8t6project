#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Encode.h"
int main (void)
{
	//启动Systick时钟
	Encode_Init();
	OLED_Init();
	
	while (1)  
	{
		OLED_ShowSignedNum(1,1,Encode_Get(),4); 
	}
}
