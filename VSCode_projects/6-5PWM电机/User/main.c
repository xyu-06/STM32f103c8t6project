#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Motor.h"
#include "Key.h"
#include "Systick.h"
int main (void)
{
    Systick_Init();
    OLED_Init();
    Motor_Init();
    Key_Init();
	while (1)
    {
        Key_Delay();
    }
}


