#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"

void SysTickInitial(void)
{
	SysTickPeriodSet(TheSysClock);	//SysTick计数值装载
	SysTickEnable(); 				//SysTick使能
}
