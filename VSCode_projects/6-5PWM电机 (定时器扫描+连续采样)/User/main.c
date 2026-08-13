#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Systick.h"
int main (void)
{
    Systick_Init();
    SoftTimer_Start(TIMER_KEY_SCAN,5);
    OLED_Init();
    Motor_Init();
    Key_Init();
	while (1)
    {
        if(Timers[TIMER_KEY_SCAN].Flag)
        {
            Timers[TIMER_KEY_SCAN].Flag=0;
            Key_Scan();
        }
    }
}


