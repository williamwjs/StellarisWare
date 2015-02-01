#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "NixieTubeConfigure.h"
#include "PWMConfigure.h"
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
			BuzzerBeep(ALARM_SOUND_PERIOD,TheSysClock/5);
			CounterSecond++;
			if (CounterSecond==60)
			{
				CounterSecond=0;
				CounterMinute++;
			}
			if (CounterMinute==60)	CounterMinute=0;
			sprintf(NixieTube,"%04u:",CounterMinute*100+CounterSecond);
		}
	}
}

void Timer1A_ISR(void)
{
	unsigned long ulStatus;		 	
	ulStatus=TimerIntStatus(TIMER1_BASE,true);	//读取中断状态
	TimerIntClear(TIMER1_BASE,ulStatus);		//清除该中断状态
	//此处不直接填TIMER_TIMA_TIMEOUT为防止TimerA的其他中断误触发，并在下面分支
	
	if(ulStatus & TIMER_TIMA_TIMEOUT) 			//确认中断源
		PWMGenDisable(PWM_BASE,PWM_GEN_2);
}
