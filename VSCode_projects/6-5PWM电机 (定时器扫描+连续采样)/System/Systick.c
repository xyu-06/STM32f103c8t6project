/**
  ******************************************************************************
  * @file    Systick.c
  * @brief   SysTick 1ms 时间基准 + 软件定时器实现
  * @note    1. Systick_Init 在 main 开头调用一次
  *          2. SoftTimer_Update 在 SysTick_Handler 中断里每 1ms 调用一次
  *          3. 主循环查询 Timers[idx].Flag 判断是否到点
  ******************************************************************************
  */

#include "stm32f10x.h"
#include "Systick.h"

/* ========== 全局时间戳（1ms 自增，供消抖/计时使用） ========== */
volatile uint32_t Systick_Count = 0;

/* ========== 软件定时器池 ========== */
SoftTimer_TypeDef Timers[TIMER_COUNT];

/**
  * @brief  初始化 SysTick：产生 1ms 周期中断
  * @note   启动文件已调用 SystemInit，这里不要再调用
  * @retval 无
  */
void Systick_Init(void)
{
    /* 72MHz / 1000 = 72000 个时钟周期 = 1ms */
    SysTick_Config(SystemCoreClock / 1000);
}

/**
  * @brief  启动/重置一个软件定时器
  * @param  idx    定时器编号（见 Systick.h 中的宏）
  * @param  period 定时周期，单位 ms
  * @retval 无
  */
void SoftTimer_Start(uint8_t idx, uint16_t period)
{
    Timers[idx].Period  = period;   /* 设置周期 */
    Timers[idx].Counter = 0;        /* 计数值清零，从头计时 */
    Timers[idx].Flag    = 0;        /* 清除到点标志 */
}

/**
  * @brief  软件定时器节拍更新
  * @note   在 SysTick_Handler 中每 1ms 调用一次；
  *         遍历所有定时器，计数自增，达到周期则清零并置标志
  * @retval 无
  */
void SoftTimer_Update(void)
{
    uint8_t i;

    for (i = 0; i < TIMER_COUNT; i++)
    {
        /* 用 >= 而不是 ==，防止计数跳变时漏判 */
        if (++Timers[i].Counter >= Timers[i].Period)
        {
            Timers[i].Counter = 0;  /* 归零，重新计时 */
            Timers[i].Flag    = 1;  /* 置到点标志 */
        }
    }
}
