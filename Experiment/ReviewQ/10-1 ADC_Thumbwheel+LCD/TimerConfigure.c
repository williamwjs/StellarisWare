#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "TimerConfigure.h"

void TimerInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);		//TIMER0使能
	TimerConfigure(TIMER0_BASE,TIMER_CFG_32_BIT_PER); 	//设置为32位周期定时器
	TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock));	//TIMER0A装载计数值
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);		//使能Timer0A超时中断
	IntEnable(INT_TIMER0A);								//开启TIMER0A中断源

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
/****************************Complete the code!!************************************/
	TimerConfigure(TIMER1_BASE, TIMER_CFG_32_BIT_OS);	//设置TIMER1为32位单次触发定时器
/***********************************************************************************/
	TimerLoadSet(TIMER1_BASE,TIMER_A,(TheSysClock/5));
	TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
	IntEnable(INT_TIMER1A);
}

