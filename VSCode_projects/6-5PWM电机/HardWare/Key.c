#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"
volatile uint32_t Exit_Time;
volatile uint8_t flat;
extern volatile uint32_t Systick_Count;
static int8_t direction=1;
static uint8_t speed=40;
void Key_Init(void)
{
	Motor_Direction(direction);
	Motor_Speed(speed);
	OLED_ShowString(1,1,"Speed:");
    OLED_ShowNum(1,7,speed,2);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init (GPIOA,&GPIO_InitStruct);

	//开启AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//配置exit
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line3|EXTI_Line5;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);

	//AFIO中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);

	//配置NVIC

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI3_IRQHandler(void)
{
	if ( EXTI_GetITStatus(EXTI_Line3)==SET)
	{
		flat=1;
		Exit_Time=Systick_Count;
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void EXTI9_5_IRQHandler(void)
{
	if ( EXTI_GetITStatus(EXTI_Line5)==SET)
	{
		flat=2;
		Exit_Time=Systick_Count;
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

void Key_Delay(void)
{
	if (flat)
	{
		switch (flat)
		{
		case 1:
		if (Systick_Count-Exit_Time>=20)
		{
			flat=0;
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==RESET)
			{
				direction=-direction;
				Motor_Direction(direction);
			}
		}		
			break;
		
		case 2:
		if (Systick_Count-Exit_Time>=20)
		{
			flat=0;
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)==RESET)
			{
				speed+=20;
				Motor_Speed(speed);
				OLED_ShowNum(1,7,speed,2);
			}
		}
		break;
		
		}
		
	}
}
