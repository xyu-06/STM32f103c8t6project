#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//初始化函数
volatile int16_t count =0;

void Encode_Init (void)
{
	//开启APB2定时器
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB,ENABLE);
	//开启AFIO定时器
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO,ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//中断线路选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	//配置EXTI中断
	//中断逻辑：当A相位下降时进中断判断B相位为高还是低，为高则正转，为低着反转；
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line=EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//选择NVIC分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//配置NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
}

int16_t Encode_Get(void)
{
	return count;
}


 //外部中断
 void EXTI1_IRQHandler(void)
 {
	 if (EXTI_GetITStatus(EXTI_Line1)==SET)
	 {
			if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==SET&&GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==RESET)
			{
				count++;
			}
			else if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==RESET&&GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==RESET)
			{
				count--;
			}
	 }
	 EXTI_ClearITPendingBit(EXTI_Line1);
 }
 







