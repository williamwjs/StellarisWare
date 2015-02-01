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
char tempMessage[40];

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
/****************************Complete the code!!************************************/
					sprintf(NixieTube,"%04u:", SetMinute*100+SetSecond);	//米字冠输出设置时间
/**********************************************************************************/
					SetFlag=1;
					SetBitFlag=0;
/****************************Complete the code!!************************************/
					BuzzerBeep(SET_SOUND_PERIOD,TheSysClock/5);		//使用BuzzerBeep函数发出短时设置音
/**********************************************************************************/
					TimerDisable(TIMER0_BASE,TIMER_A);
					LCDDrawingFlag_Pause=true;
					
					sprintf(tempMessage,"%2d:%2d\n\r",SetMinute,SetSecond);
					UARTStringPut(UART0_BASE,tempMessage);
				}
				else
				{
/****************************Complete the code!!************************************/
					sprintf(NixieTube,"%04u:", CounterMinute*100+CounterSecond);	//米字冠输出计时时间
/**********************************************************************************/
					SetFlag=0;
/****************************Complete the code!!************************************/
					BuzzerBeep(SET_SOUND_PERIOD,TheSysClock/5);//使用BuzzerBeep函数发出短时设置音
/**********************************************************************************/
					TimerEnable(TIMER0_BASE,TIMER_A);
					LCDDrawingFlag_Running=true;
				}
				LEDOverturn(LED_1);
				KeyNumber=0;
				break;
			}
			case	2:
			{
				if (SetFlag)
					SetBitFlag=1-SetBitFlag;
				KeyNumber=0;
				break;
			}
			case	3:
			{
				if (SetFlag)
					SetBitFlag=1-SetBitFlag;
				KeyNumber=0;
				break;
			}
			case	4:
			{
				if (SetFlag)
				{	
					if (SetBitFlag)
					{
						SetMinute++;
						if (SetMinute==60)	SetMinute=0;
					}
					else
					{
						SetSecond++;
						if (SetSecond==60) SetSecond=0;
					}
/****************************Complete the code!!************************************/
					sprintf(NixieTube,"%04u:", SetMinute*100+SetSecond);	//米字冠输出设置时间
/**********************************************************************************/
				}
				KeyNumber=0;
				break;
			}
			case	5:
			{
				if (SetFlag)
				{
					if (SetBitFlag)
					{
						if (SetMinute>0)	SetMinute--;
						else	SetMinute=59;
					}
					else
					{
						if (SetSecond>0) SetSecond--;
						else	SetSecond=59;
					}
/****************************Complete the code!!************************************/
					sprintf(NixieTube,"%04u:", SetMinute*100+SetSecond);	//米字冠输出设置时间
/**********************************************************************************/
				}
				KeyNumber=0;
				break;
			}
			default:	break;
		}
	}
}

