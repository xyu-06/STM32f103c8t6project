#include "stm32f10x.h"
//PWM初始化函数
void PWM_Init(void){
    //开启GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //配置GPIOA
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    //开启定时器时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //选择内部时钟
    TIM_InternalClockConfig(TIM2);
    //配置时基单元
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
    TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period=100-1;//ARR自动重装值
    TIM_TimeBaseInitStructure.TIM_Prescaler=720-1;//预分频数
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
    
    //配置输出比较
    TIM_OCInitTypeDef TIM_OCInitStructure;
    //对输出比较的结构体赋初始值
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState=ENABLE;
    TIM_OCInitStructure.TIM_Pulse=0;
    TIM_OC1Init(TIM2,&TIM_OCInitStructure);

    //开启定时器计算
    TIM_Cmd(TIM2,ENABLE);
}

void PWM_Changevalue(uint8_t value)
{
    TIM_SetCompare1(TIM2,value);
}
