#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "TimerConfigure.h"

void TimerInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);		//TIMER0使能
	TimerConfigure(TIMER0_BASE,TIMER_CFG_A_PERIODIC); 	//设置为16位周期定时器
	TimerPrescaleSet(TIMER0_BASE,TIMER_A,255);
	//TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock/3));	//TIMER0A装载计数值
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);		//使能Timer0A超时中断使能
	IntEnable(INT_TIMER0A);								//开启TIMER0A中断源
}
