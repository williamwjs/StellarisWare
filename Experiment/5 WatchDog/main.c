#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"
#include "WatchDogConfigure.h"

unsigned char BlinkFlag=true; 
 	
int main(void)											//主函数
{
	//初始化
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();								

	LEDOn(LED_ALL);
	while (!(KeyPress(KEY_LEFT) |
			 KeyPress(KEY_RIGHT) |
			 KeyPress(KEY_UP) |
			 KeyPress(KEY_DOWN)));
	LEDOff(LED_ALL);	

	IntMasterEnable();									//外围中断开启（除了SysTick外的所有中断都要开启）
	SysTickEnable();									//SysTick开始计数
	TimerEnable(TIMER0_BASE,TIMER_A);					//TIMER0开始计数
	WatchDogInitial();									//启动看门狗模块

	while(1);
}
