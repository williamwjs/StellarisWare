#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "TimerISR.h"

void Timer0A_ISR(void)						//1S��ʱ����
{
	unsigned long ulStatus;		 	
	ulStatus=TimerIntStatus(TIMER0_BASE,true);	//��ȡ�ж�״̬
	TimerIntClear(TIMER0_BASE,ulStatus);		//������ж�״̬
	//�˴���ֱ����TIMER_TIMA_TIMEOUTΪ��ֹTimerA�������ж��󴥷������������֧
	
	if(ulStatus & TIMER_TIMA_TIMEOUT) 			//ȷ���ж�Դ
	{
		LEDOverturn(LED_ALL);
	}
}
