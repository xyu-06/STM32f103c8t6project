#include "stm32f10x.h"                  // Device header
#include "OLED.h"
//#include "Timer.h"
uint16_t numble;
volatile uint32_t Systick_Count;
int main (void)
{
	SystemInit();
	OLED_Init();
	//Timer_Init();
	OLED_ShowString(1,1,"Num:");
	OLED_ShowNum(1,5,numble,5);
	SysTick_Config(SystemCoreClock/1000);
	while (1)
	{
		if (Systick_Count>=1000)
		{
			Systick_Count-=1000;
			numble++;
			OLED_ShowNum(1,5,numble,5);
		}	
	}
}


//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//		numble++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}


