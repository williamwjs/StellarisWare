#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"

#define	SECOND 4000000
#define MILLISECOND 4000
#define MICROSECOND 4

void DelayS(int time)			
{
	time=time*SECOND;
	while((time--)>0);
}

void DelayMS(int time)
{
	time=time*MILLISECOND;
	while((time--)>0);
}

void DelayUS(long int time)
{
	time=time*MICROSECOND;
	while((time--)>0);
}

/*
	�������ܣ���������LED0��LED1
	Ӳ�����ӣ�LED0��JP2��Yellow)-->PF3	LED1(JP3,Green)-->PF2	�͵�ƽ��Ч
*/

int main(void)									//������
{
	ClockInitial();	
	GPIOInitial();
	while(1)	
	{
		if (KeyPress(KEY_PRESS))
		{
			LEDOn(LED_1);
			LEDOff(LED_0);
			SysCtlDelay(TheSysClock/6);			//��ʱһ��ʱ�䣬ʹ�ÿ⺯�����ӳ�ʱ��=3��������ϵͳʱ�����ڡ��ô�Ϊ0.5S
			LEDOn(LED_0);																					   
			LEDOff(LED_1);
			DelayMS(500);	 					//��ʱһ��ʱ�䣬ʹ������delay�������˴�Ϊ0.5S
		}
		else
			LEDOff(LED_ALL);
	}
}
