#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"

void SysTickInitial(void)
{
	SysTickPeriodSet(TheSysClock/2);	//SysTick����ֵװ��
	SysTickIntEnable(); 			  	//SysTick�ж�ʹ��
}
