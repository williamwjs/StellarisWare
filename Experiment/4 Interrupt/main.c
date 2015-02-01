#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"

unsigned char ShiningEnable=true;	//hw_types中定义，必须小写
 	
int main(void)						
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();	
	IntMasterEnable();									//外围中断开启（除了SysTick外的所有中断都要开启）

	SysTickEnable();									//SysTick开始计数
	TimerEnable(TIMER0_BASE,TIMER_A);					//TIMER0开始计数

	while(1);
}
