#include "stm32f10x.h"                  // Device header


 volatile uint8_t count=0;
 volatile uint32_t Last_Time =0;
 volatile uint8_t flat = 0;
 //定义心跳次数变量，
 volatile uint32_t Systick_Count =0;
 
 void CountSensor_Init(void)
 {
	 //开启systick内核时钟,时间为1sm
	 SysTick_Config(SystemCoreClock/1000);
	 
	 //开启GPIO时钟
	 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	 //开启AFIO时钟
	 RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO,ENABLE);
	 //配置GPIO时钟
	 GPIO_InitTypeDef GPIO_InitStruct;
	 GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	 GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	 GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	 GPIO_Init (GPIOA,&GPIO_InitStruct);
	 //AFIO外设中断引脚选择
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	 //EXTI初始化
	 EXTI_InitTypeDef EXTI_InitStruct;
	 EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	 EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	 EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	 EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
		EXTI_Init(&EXTI_InitStruct);
	 //配置NVIC
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	 NVIC_InitTypeDef NVIC_InitStruct;
	 NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	 NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	 NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	 NVIC_Init(&NVIC_InitStruct);
 }
 //未进行遮挡时输入为低电平
 //遮挡输入为高电平

 
 uint8_t CountSensor_Get(void)
 {
	 return count;
 }
 
 //外部中断
 void EXTI0_IRQHandler(void)
 {
 	 if (EXTI_GetITStatus(EXTI_Line0)==SET)
 	 {
 	 EXTI->IMR &=~(1<<0);
 	 EXTI_ClearITPendingBit(EXTI_Line0);
 	 Last_Time = Systick_Count;
 	 flat =1;
 	 }
 }
 
 void Systick_Delay(void)
 {
	 if(flat==1)
	 {
		 if ((Systick_Count-Last_Time)>20)
		 {
			 if (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==SET)
			 {
			 count++;
			 }
			 EXTI_ClearITPendingBit(EXTI_Line0);
			 EXTI->IMR |=(1<<0);
			 flat =0;
		 }
	 }
 }
 
 //systick系统时钟中断
// void SysTick_Handler(void)
// {
//	 Systick_Count;
// }