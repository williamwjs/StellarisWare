#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "WatchDogConfigure.h"
#include "SysCtlConfigure.h"

void WatchDogInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG);			//使能看门狗模块 
 	WatchdogResetEnable(WATCHDOG_BASE);					//使能看门狗复位功能 
 	WatchdogStallEnable(WATCHDOG_BASE);					//使能调试器暂停看门狗计数 
 	WatchdogReloadSet(WATCHDOG_BASE, TheSysClock*2);	//设置看门狗装载值 
 	WatchdogEnable(WATCHDOG_BASE);						//使能看门狗 
 	WatchdogLock(WATCHDOG_BASE);						//锁定看门狗 		
}
 
void WatchDogFeed(void)
{
	WatchdogUnlock(WATCHDOG_BASE);     					//解除锁定 
	WatchdogIntClear(WATCHDOG_BASE);					//清除中断状态，即喂狗操作 
	WatchdogLock(WATCHDOG_BASE);						//重新锁定
}
