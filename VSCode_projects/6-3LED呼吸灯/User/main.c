#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "Delay.h"
uint8_t i =0;
int main (void)
{
    OLED_Init();
    PWM_Init();
	while (1)
    {
        /* code */
        for ( i=0;i<100;i++)
        {
            TIM_SetCompare1(TIM2,i);
            Delay_ms(15);
        }
         for ( i=0;i<100;i++)
        {
            TIM_SetCompare1(TIM2,100-i);
            Delay_ms(15);
        }

    }
    
}
