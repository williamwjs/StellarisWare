#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"

void SysTickInitial(void)
{
	SysTickPeriodSet(TheSysClock/200);	//SysTick计数值装载，1/200秒
	SysTickIntEnable(); 				//SysTick中断使能
}
