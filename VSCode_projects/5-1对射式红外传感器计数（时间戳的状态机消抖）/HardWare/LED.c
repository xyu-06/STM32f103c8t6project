#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitSturct;
	GPIO_InitSturct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitSturct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitSturct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSturct);
	GPIO_WriteBit(GPIOA,GPIO_Pin_0|GPIO_Pin_1,Bit_SET);
}

void LEDA0_OFF(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
}

void LEDA0_ON(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
}

void LEDA0_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==0)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	}
	else
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	}
}

void LEDA1_OFF(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
}

void LEDA1_ON(void)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
}

void LEDA1_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);
	}
	else
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	}
}