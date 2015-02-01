#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "TimerISR.h"

void Timer0A_ISR(void)						//1S定时函数
{
	unsigned long ulStatus;		 	
	ulStatus=TimerIntStatus(TIMER0_BASE,true);	//读取中断状态
	TimerIntClear(TIMER0_BASE,ulStatus);		//清除该中断状态
	//此处不直接填TIMER_TIMA_TIMEOUT为防止TimerA的其他中断误触发，并在下面分支
	
	if(ulStatus & TIMER_TIMA_TIMEOUT) 			//确认中断源
	{
		LEDOverturn(LED_ALL);
	}
}
