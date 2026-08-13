#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"
uint32_t count;
int main (void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"Num:");
	OLED_ShowNum(1,5,count,5);
	while (1)
	{
		
	}
}


void TIM2_IRQHandler (void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET )
	{
		count++;
		OLED_ShowNum(1,5,count,5);
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}

