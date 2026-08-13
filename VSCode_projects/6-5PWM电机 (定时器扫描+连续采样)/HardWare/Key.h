#ifndef __Key_H
#define __Key_H
typedef struct
{
    GPIO_TypeDef *GPIOx;       /* 端口 */
    uint16_t      Pin;         /* 引脚 */
    uint8_t       state;       /* 状态机：0=松开 1=消抖中 2=按住计时 */
    uint8_t       count;         /* 消抖采样计数 */
    uint16_t      hold_count;    /* 按住计时（每 5ms +1） */
    uint8_t       long_done;   /* 长按已触发标记 */
    void (*ShortAction)(void); /* 短按回调 */
    void (*LongAction)(void);  /* 长按回调 */
} Key_TypeDef;

/* 长按阈值：200 次 × 5ms = 1 秒 */
#define LONG_PRESS_TICKS  200
/* 按键编号（供外部引用） */
#define KEY1  0    /* PA3：切换方向 */
#define KEY2  1    /* PA5：加速 */
#define KEY3  2    /* PA7：减速 */
#define KEY_NUM  3


void Key_Init(void);
void Key_Scan(void);
#endif