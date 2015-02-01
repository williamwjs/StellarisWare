#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "TimerConfigure.h"

void TimerInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);			//ʹ��TIMER0
	TimerConfigure(TIMER0_BASE, TIMER_CFG_32_BIT_PER);		//����Ϊ32λ����ʽ������
	TimerLoadSet(TIMER0_BASE,TIMER_A, (TheSysClock/3)); 	//�������Ϊ0.33S		
	TimerEnable(TIMER0_BASE,TIMER_A);						//TIMER0��ʼ����
}
