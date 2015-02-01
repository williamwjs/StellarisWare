#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "I2CConfigure.h"
#include "PWMConfigure.h"
#include "SysTickISR.h"

#define KEY_TRIGGERTIME_FIRST	15
#define KEY_TRIGGERTIME_HOLD	150
#define KEY_TRIGGERTIME_ROLL	30

volatile unsigned char KeyNumber=0;		//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
volatile unsigned char KeyNumberPresent=0;
volatile unsigned char KeyHoldFlag=0;

volatile unsigned long BreathingLEDPWM=BreathingLEDPeriod;
volatile unsigned char BreathingLEDFlag=0;	//0-up 1-down

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
/****************************Put your code here!!************************************/
	//实现呼吸灯
	//SysTick中断每4ms执行一次
	//每执行一次少量改变PWM的占空比
	//实现LED灯慢慢变亮再慢慢变暗的效果
	switch (BreathingLEDPWM)
	{
		case 1:	
		{
			BreathingLEDFlag=0;
			break;
		}
		case BreathingLEDPeriod/2:
		{
			if (BreathingLEDFlag)
				LEDOn(LED_1);
			else
				LEDOff(LED_1);
			break;
		}
		case BreathingLEDPeriod:
		{
			BreathingLEDFlag=1;
			break;
		}
		default:	break;
	}
	if (BreathingLEDFlag)
	{
		BreathingLEDPWM--;//递减BreathingLEDPWM
	}
	else
	{
		BreathingLEDPWM++;//递增BreathingLEDPWM
	}
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,BreathingLEDPWM);		//更改PWM波
/**********************************************************************************/
}
