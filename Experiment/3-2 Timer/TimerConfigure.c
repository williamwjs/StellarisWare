#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "TimerConfigure.h"

void TimerInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);			//使能TIMER0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_32_BIT_PER);		//设置为32位周期式计数器
	TimerLoadSet(TIMER0_BASE,TIMER_A, (TheSysClock/3)); 	//溢出周期为0.33S		
	TimerEnable(TIMER0_BASE,TIMER_A);						//TIMER0开始计数
}
