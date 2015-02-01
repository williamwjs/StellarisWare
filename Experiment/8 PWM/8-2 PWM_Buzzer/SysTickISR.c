#include "GPIODriverConfigure.h"
#include "I2CConfigure.h"
#include "SysTickISR.h"

#define KEY_TRIGGERTIME_FIRST	15
#define KEY_TRIGGERTIME_HOLD	150
#define KEY_TRIGGERTIME_ROLL	30

volatile unsigned char KeyNumber=0;		//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
volatile unsigned char KeyNumberPresent=0;
volatile unsigned char KeyHoldFlag=0;

void SysTick_ISR(void)					//SysTick中断函数，此处5ms定时，作时间片用
{	
	static unsigned char KeyWaitTime=0;
	static unsigned char KeyNumberHistory=0;
	static unsigned char KeyCounter=0;
	KeyNumberHistory=KeyNumberPresent;									
	KeyNumberPresent=GetKeyNumber();
	if ((KeyNumberPresent==0) || (KeyNumberPresent!=KeyNumberHistory))
	{
		KeyCounter=0;
		KeyNumber=0;
		KeyHoldFlag=0;
	}
	else
	{
		switch (KeyHoldFlag)
		{
			case	0:	KeyWaitTime=KEY_TRIGGERTIME_FIRST;break;
			case	1:	KeyWaitTime=KEY_TRIGGERTIME_HOLD;break;
			default:	KeyWaitTime=KEY_TRIGGERTIME_ROLL;break;
		}
		if (KeyCounter < KeyWaitTime)	KeyCounter++;	
		else
		{
			KeyNumber=KeyNumberPresent;
			KeyHoldFlag++;
			KeyCounter=0;
		}
	}
	I2C0DeviceRefresh();
}
