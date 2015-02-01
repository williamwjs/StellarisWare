#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "TimerConfigure.h"

void TimerInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);		//TIMER0ʹ��
	TimerConfigure(TIMER0_BASE,TIMER_CFG_32_BIT_PER); 	//����Ϊ32λ���ڶ�ʱ��
	TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock));	//TIMER0Aװ�ؼ���ֵ
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);		//ʹ��Timer0A��ʱ�ж�
	IntEnable(INT_TIMER0A);								//����TIMER0A�ж�Դ

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
/****************************Complete the code!!************************************/
	TimerConfigure(TIMER1_BASE, TIMER_CFG_32_BIT_OS);	//����TIMER1Ϊ32λ���δ�����ʱ��
/***********************************************************************************/
	TimerLoadSet(TIMER1_BASE,TIMER_A,(TheSysClock/5));
	TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
	IntEnable(INT_TIMER1A);
}

