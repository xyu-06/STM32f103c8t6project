/**
  ******************************************************************************
  * @file    Systick.h
  * @brief   SysTick 系统定时器 + 软件定时器驱动（对外接口）
  * @note    基于 SysTick 1ms 中断实现多路软件定时器
  ******************************************************************************
  */

#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

/* ========== 软件定时器结构体 ========== */
typedef struct
{
    uint16_t Period;            /* 定时周期，单位 ms */
    uint16_t Counter;           /* 当前计数值，每 1ms 自增一次 */
    volatile uint8_t Flag;      /* 到点标志：1=定时到，主循环判断后清零 */
} SoftTimer_TypeDef;

/* ========== 定时器编号（需要新定时器时在此添加） ========== */
#define TIMER_KEY_SCAN     0    /* 按键扫描定时器 */
#define TIMER_COUNT        1    /* 定时器总个数 */

/* 定时器池数组：定义在 Systick.c，其他文件通过 extern 只读访问 */
extern SoftTimer_TypeDef Timers[TIMER_COUNT];

/* ========== 对外接口 ========== */
void Systick_Init(void);                            /* 初始化 SysTick：1ms 心跳 */
void SoftTimer_Start(uint8_t idx, uint16_t period); /* 启动/重置一个软件定时器 */
void SoftTimer_Update(void);                        /* 1ms 节拍更新（中断里调用） */

#endif /* __SYSTICK_H */
