//#include  "stm32f10x.h"                  // Device header
//void Timer_Init(void)
//{
//	//开启时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE );
//	//选择内部时钟
//	TIM_InternalClockConfig(TIM2);
//	//配置时基单元
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStruct.TIM_Period=10000-1;
//	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;
//	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
//	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
//	//清除标识位，避免初始完成就进中断
//	TIM_ClearFlag(TIM2,TIM_IT_Update);
//	//使能中断
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );
//	//配置NVIC中断
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	NVIC_InitTypeDef NVIC_InitStruct;
//	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE ;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&NVIC_InitStruct);
//	//启动定时器
//	TIM_Cmd(TIM2,ENABLE );
//}

///*void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}
//*/

	
