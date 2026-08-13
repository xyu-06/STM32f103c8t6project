#include "stm32f10x.h"
volatile uint32_t Systick_Count;
void Systick_Init(void)
{
    SystemInit();
    //1ms计时
    SysTick_Config(SystemCoreClock/1000);
}