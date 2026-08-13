#include "stm32f10x.h"                  // Device header
#include "Delay.h"
uint16_t count =0;
//初始化函数
void CountSensor_Init(void)
{
	//开启APB2时钟
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	//开启AFIO时钟
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO,ENABLE);
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//配置AFIO外部中断引脚
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	//配置EXTI外部中断
  EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	//配置NVIC
	//配置NVIC分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);

}
//采用阻塞式，中断关开消抖计数
uint16_t CountSensor_Get()
{
	return count;
}

void EXTI0_IRQHandler (void)
{
	if (EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		EXTI->IMR&=~(1<<0);
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET)//上升沿SET，下降沿RESET，上下沿SET||RESET
		{
		count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
		EXTI->IMR|=(1<<0);
	}
}

