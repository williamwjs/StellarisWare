#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "GPIODriverConfigure.h"
#include "I2CConfigure.h"
#include "NixieTubeConfigure.h"
#include "PWMConfigure.h"
#include "LCDDisplay.h"
#include "SysTickISR.h"

#define KEY_TRIGGERTIME_FIRST	15
#define KEY_TRIGGERTIME_HOLD	150
#define KEY_TRIGGERTIME_ROLL	30

volatile unsigned char KeyNumber=0;			//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
volatile unsigned char KeyNumberPresent=0;
volatile unsigned char KeyHoldFlag=0;

volatile unsigned char ADCTriggerCounter=0;

void SysTick_ISR(void)						//SysTick中断函数，此处5ms定时，作时间片用
{											//处理按键和数码管
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
	//键盘信息处理
	if (SystemActivatedFlag)
	{
		switch (KeyNumber)
		{
			case	1:
			{
				if (SetFlag==0)
				{	
					sprintf(NixieTube,"%04u:",SetMinute*100+SetSecond);
					SetFlag=1;
					BuzzerBeep(SET_SOUND_PERIOD,TheSysClock/5);
					TimerDisable(TIMER0_BASE,TIMER_A);
					LCDDrawingFlag_Pause=true;
				}
				else
				{
					sprintf(NixieTube,"%04u:",CounterMinute*100+CounterSecond);
					SetFlag=0;
					BuzzerBeep(SET_SOUND_PERIOD,TheSysClock/5);
					TimerEnable(TIMER0_BASE,TIMER_A);
					LCDDrawingFlag_Running=true;
				}
				LEDOverturn(LED_1);
				KeyNumber=0;
				break;
			}
			case	4:
			{
				if (SetFlag)
				{	
					switch(SetBitFlag)
					{
						case 0:	
						{
							SetSecond++;
							if (SetSecond >59) SetSecond=0;
							break;
						}
						case 1:
						{
							SetSecond+=10;
							if (SetSecond >59)	SetSecond-=60;
							break;
						}
						case 2:
						{
							SetMinute++;
							if (SetMinute >59) SetMinute=0;
							break;
						}
						case 3:
						{
							SetMinute+=10;
							if (SetMinute >59) SetMinute-=60;
							break;
						}
						default:	break;
					}
					sprintf(NixieTube,"%04u:",SetMinute*100+SetSecond);
				}
				KeyNumber=0;
				break;
			}
			case	5:
			{
				if (SetFlag)
				{
					switch(SetBitFlag)
					{
						case 0:	
						{
							if (SetSecond >0)	SetSecond--;
							else	SetSecond=59;
							break;
						}
						case 1:
						{
							if (SetSecond >9)	SetSecond-=10;
							else	SetSecond+=50;
							break;
						}
						case 2:
						{
							if (SetMinute >0)	SetMinute--;
							else	SetMinute=59;
							break;
						}
						case 3:
						{
							if (SetMinute >9)	SetMinute-=10;
							else	SetMinute+=50;
							break;
						}
						default:	break;
					}
					sprintf(NixieTube,"%04u:",SetMinute*100+SetSecond);
				}
				KeyNumber=0;
				break;
			}
			default:	break;
		}
		ADCTriggerCounter++;
		if (ADCTriggerCounter==200)
		{
			ADCTriggerCounter=0;
			ADCProcessorTrigger(ADC1_BASE,1);		//处理器触发ADC，序列1采样
		}
		else
		{
			if (ADCTriggerCounter%25==0)
				ADCProcessorTrigger(ADC1_BASE,0);	//处理器触发ADC，序列0采样
		}
	}
}
