#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"

void SysTickInitial(void)
{
	SysTickPeriodSet(TheSysClock/200);	//SysTick����ֵװ�أ�1/200��
	SysTickIntEnable(); 				//SysTick�ж�ʹ��
}
