#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"

int main (void)
{
  CountSensor_Init();
	OLED_Init();
	while (1)
	{
	OLED_ShowString(1,1,"Numble:");
	OLED_ShowNum(1,8,CountSensor_Get(),4);
	}
}
