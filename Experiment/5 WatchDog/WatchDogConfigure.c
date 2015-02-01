#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "WatchDogConfigure.h"
#include "SysCtlConfigure.h"

void WatchDogInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WDOG);			//ʹ�ܿ��Ź�ģ�� 
 	WatchdogResetEnable(WATCHDOG_BASE);					//ʹ�ܿ��Ź���λ���� 
 	WatchdogStallEnable(WATCHDOG_BASE);					//ʹ�ܵ�������ͣ���Ź����� 
 	WatchdogReloadSet(WATCHDOG_BASE, TheSysClock*2);	//���ÿ��Ź�װ��ֵ 
 	WatchdogEnable(WATCHDOG_BASE);						//ʹ�ܿ��Ź� 
 	WatchdogLock(WATCHDOG_BASE);						//�������Ź� 		
}
 
void WatchDogFeed(void)
{
	WatchdogUnlock(WATCHDOG_BASE);     					//������� 
	WatchdogIntClear(WATCHDOG_BASE);					//����ж�״̬����ι������ 
	WatchdogLock(WATCHDOG_BASE);						//��������
}
