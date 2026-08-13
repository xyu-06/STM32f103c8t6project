#include "stm32f10x.h" // Device header
#include "Motor.h"
#include "OLED.h"
#include "Key.h"
static int8_t direction = 1;
static uint8_t speed = 40;

/* KEY1：短按切换方向,电机停转 */
static void Key1_Short(void)
{
	direction = -direction; 
	Motor_Direction(direction);
}
static void Key1_Long(void)
{
	speed = 0;
	Motor_Speed(speed);
}

/* KEY2：短按加速，长按直接最大 */
static void Key2_Short(void)
{
	speed += 20;
	if (speed > 99)
		speed = 99;
	Motor_Speed(speed);
}

static void Key2_Long(void)
{
	speed = 99;
	Motor_Speed(speed);
}

/* KEY3：短按减速，长按停止 */
static void Key3_Short(void)
{
	if (speed > 20)
		speed -= 20;
	else
		speed = 0;
	Motor_Speed(speed);
}

static void Key3_Long(void)
{
	speed = 0;
	Motor_Speed(speed);
}

static Key_TypeDef Keys[KEY_NUM] = {
	/*  KEY1(PA3)：短按切方向，长按也切方向（或自定义） */
	{GPIOA, GPIO_Pin_3, 0, 0, 0, 0, Key1_Short, Key1_Long},
	/*  KEY2(PA5)：短按 +20，长按 +99 直接最大 */
	{GPIOA, GPIO_Pin_5, 0, 0, 0, 0, Key2_Short, Key2_Long},
	/*  KEY3(PA7)：短按 -20，长按 = 0 停止 */
	{GPIOA, GPIO_Pin_7, 0, 0, 0, 0, Key3_Short, Key3_Long},
};

void Key_Init(void)
{
	Motor_Direction(direction);
	Motor_Speed(speed);
	OLED_ShowString(1, 1, "Speed:");
	OLED_ShowNum(1, 7, speed, 2);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* 扫描函数：每 5ms 调用一次（软件定时器驱动） */
void Key_Scan(void)
{
	
    for (uint8_t i = 0; i < KEY_NUM; i++)
    {
        uint8_t level = GPIO_ReadInputDataBit(Keys[i].GPIOx, Keys[i].Pin);
        switch (Keys[i].state)
        {
        /* -------- 状态 0：松开，等待按下 -------- */
        case 0:
            if (level == RESET)          /* 检测到按下 */
            {
                Keys[i].state = 1;       /* 进入消抖 */
                Keys[i].count = 0;
            }
            break;
        /* -------- 状态 1：消抖中 -------- */
        case 1:
            if (level == RESET)          /* 连续按下 */
            {
                if (++Keys[i].count >= 3)  /* 3次×5ms=15ms 消抖完成 */
                {
                    Keys[i].state = 2;   /* 进入按住计时 */
                    Keys[i].hold_count = 0;
                    Keys[i].long_done = 0;
                }
            }
            else                         /* 抖动/松开，回到松开态 */
            {
                Keys[i].state = 0;
            }
            break;
        /* -------- 状态 2：按住中，区分短按/长按 -------- */
        case 2:
            if (level == RESET)          /* 还按着 */
            {
                if (++Keys[i].hold_count >= LONG_PRESS_TICKS)  /* 到 1 秒 */
                {
                    if (Keys[i].long_done == 0)
                    {
                        Keys[i].long_done = 1;   /* 标记，只触发一次 */
                        Keys[i].LongAction();   /* 触发长按 */
                    }
                }
            }
            else                         /* 松开了 */
            {
                if (Keys[i].long_done == 0)
                {
                    Keys[i].ShortAction();      /* 没长按过 → 是短按 */
                }
                Keys[i].state = 0;       /* 回到松开态 */
            }
            break;
        }
    }
}
