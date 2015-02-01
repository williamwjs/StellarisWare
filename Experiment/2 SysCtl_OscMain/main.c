#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"

#define	SECOND 4000000
#define MILLISECOND 4000
#define MICROSECOND 4

void DelayS(int time)			
{
	time=time*SECOND;
	while((time--)>0);
}

void DelayMS(int time)
{
	time=time*MILLISECOND;
	while((time--)>0);
}

void DelayUS(long int time)
{
	time=time*MICROSECOND;
	while((time--)>0);
}

/*
	函数功能：轮流点亮LED0与LED1
	硬件连接：LED0（JP2，Yellow)-->PF3	LED1(JP3,Green)-->PF2	低电平有效
*/

int main(void)									//主函数
{
	ClockInitial();	
	GPIOInitial();
	while(1)	
	{
		if (KeyPress(KEY_PRESS))
		{
			LEDOn(LED_1);
			LEDOff(LED_0);
			SysCtlDelay(TheSysClock/6);			//延时一段时间，使用库函数，延长时间=3×参数×系统时钟周期。该处为0.5S
			LEDOn(LED_0);																					   
			LEDOff(LED_1);
			DelayMS(500);	 					//延时一段时间，使用自制delay函数，此处为0.5S
		}
		else
			LEDOff(LED_ALL);
	}
}
