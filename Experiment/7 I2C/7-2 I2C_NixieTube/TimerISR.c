#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "NixieTubeConfigure.h"
#include "TimerISR.h"

void Timer0A_ISR(void)							//1S��ʱ����
{
	unsigned long ulStatus;		 	
	ulStatus=TimerIntStatus(TIMER0_BASE,true);	//��ȡ�ж�״̬
	TimerIntClear(TIMER0_BASE,ulStatus);		//������ж�״̬
	//�˴���ֱ����TIMER_TIMA_TIMEOUTΪ��ֹTimerA�������ж��󴥷������������֧
	
	if(ulStatus & TIMER_TIMA_TIMEOUT) 			//ȷ���ж�Դ
	{
		if ((CounterMinute<SetMinute) || ((CounterMinute==SetMinute) && (CounterSecond<SetSecond)))
		{
			if(LEDSerial!=0x80)	LEDSerial=LEDSerial<<1;
			else	LEDSerial=0x01;
			CounterSecond++;
			if (CounterSecond==60)
			{
				CounterSecond=0;
				CounterMinute++;
			}
			if (CounterMinute==60)	CounterMinute=0;
/****************************Complete the code!!************************************/
				sprintf(NixieTube,"%04u:", CounterMinute*100+CounterSecond);	//���ֹ������ʱʱ��
/**********************************************************************************/
		}
	}
}
