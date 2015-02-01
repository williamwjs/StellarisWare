#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "NixieTubeConfigure.h"
#include "TimerISR.h"

void Timer0A_ISR(void)							//1S定时函数
{
	unsigned long ulStatus;		 	
	ulStatus=TimerIntStatus(TIMER0_BASE,true);	//读取中断状态
	TimerIntClear(TIMER0_BASE,ulStatus);		//清除该中断状态
	//此处不直接填TIMER_TIMA_TIMEOUT为防止TimerA的其他中断误触发，并在下面分支
	
	if(ulStatus & TIMER_TIMA_TIMEOUT) 			//确认中断源
	{
		if ((CounterMinute<SetMinute) || ((CounterMinute==SetMinute) && (CounterSecond<SetSecond)))
		{
			if(LEDSerial!=0x80)	LEDSerial=LEDSerial<<1;
			else	LEDSerial=0x01;
			CounterSecond++;
			if (CounterSecond==60)
			{
				CounterSecond=0;
				CounterMinute++;
			}
			if (CounterMinute==60)	CounterMinute=0;
/****************************Complete the code!!************************************/
				sprintf(NixieTube,"%04u:", CounterMinute*100+CounterSecond);	//米字冠输出计时时间
/**********************************************************************************/
		}
	}
}
