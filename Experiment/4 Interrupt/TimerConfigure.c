#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "TimerConfigure.h"

void TimerInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);		//TIMER0ʹ��
	TimerConfigure(TIMER0_BASE,TIMER_CFG_32_BIT_PER); 	//����Ϊ32λ���ڶ�ʱ��
	TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock/3));	//TIMER0Aװ�ؼ���ֵ
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);		//ʹ��Timer0A��ʱ�ж�ʹ��
	IntEnable(INT_TIMER0A);								//����TIMER0A�ж�Դ
}
