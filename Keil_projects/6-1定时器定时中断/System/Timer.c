#include "stm32f10x.h"                  // Device header

//内部定时器中断1s

void Timer_Init(void)
{
	//开启定时器时钟
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2,ENABLE);
	
	//选择内部时钟源
	TIM_InternalClockConfig(TIM2);
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数方式
	TIM_TimeBaseInitStruct.TIM_Period=7200-1;//ARR自动重装数
	TIM_TimeBaseInitStruct.TIM_Prescaler=10000-1;//预分频数
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//高级定时器特有，重复计数次数
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	//默认上电直接进中断，先清除标志位
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//定时器使能
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );
	
	//配置NVIC分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//配置NVIC
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	//使能计数器
	TIM_Cmd(TIM2,ENABLE);
}

