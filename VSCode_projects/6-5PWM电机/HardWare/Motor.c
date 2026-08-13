#include "stm32f10x.h"
#include "PWM.h"
//电机初始化函数
void Motor_Init(void)
{ 
    PWM_Init();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}
//1为正转;-1为负转
void Motor_Direction(int8_t direction)
{
    if(direction==1)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_10);
        GPIO_ResetBits(GPIOA,GPIO_Pin_11);
    }
    if(direction==-1)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_11);
        GPIO_ResetBits(GPIOA,GPIO_Pin_10);
    }
}

void Motor_Speed(uint8_t speed)
{
    if (speed>=99) speed=99;
    PWM_Changevalue(speed);
}