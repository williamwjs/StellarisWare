#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"
#include "WatchDogConfigure.h"
#include "UARTConfigure.h"

#define TRANSCODINGSTATUS_0	0
#define TRANSCODINGSTATUS_1	1
#define TRANSCODINGSTATUS_2	2
#define TRANSCODINGSTATUS_3	3

unsigned char UARTSendFlag=false;
unsigned char TranscodingStatus = TRANSCODINGSTATUS_0;		//ת����־λ
	
int main(void)						
{
	char tempChar;	

	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();
	UART0Initial();
	UARTStringPut(UART0_BASE,"Initial Done!\r\n");
	UARTStringPut(UART0_BASE,"Press the KEY to continue~\r\n");

	LEDOn(LED_ALL);
	while (!KeyPress(KEY_PRESS));
	LEDOff(LED_ALL);	
	UARTStringPut(UART0_BASE,"GO! ! !\r\n");	

	IntMasterEnable();							//��Χ�жϿ���
	SysTickEnable();							//��SysTick�ж�
	TimerEnable(TIMER0_BASE,TIMER_A);			//��TIMER0

	while(1)
	{
		tempChar=UARTCharGet(UART0_BASE);
		//ת��ʵ�ֹ���
		if (TranscodingStatus == TRANSCODINGSTATUS_1)	
		{ 
			if (tempChar>= 97 && tempChar<= 122)
			{
				tempChar=tempChar-32;
			}
		}
		
		if (TranscodingStatus == TRANSCODINGSTATUS_2)
		{
			if (tempChar >= 65 && tempChar <= 90)
			{	
				tempChar=tempChar+32;
			}
		}

		if (TranscodingStatus == TRANSCODINGSTATUS_3)
		{
			if (tempChar>= 97 && tempChar<= 122)
			{
				tempChar=tempChar-32;
			}
			else
			{
				if (tempChar >= 65 && tempChar <= 90)
				{	
					tempChar=tempChar+32;
				}
			}
		} 
		UARTCharPut(UART0_BASE,tempChar); 				//����
		UARTSendFlag=true;
		if (tempChar=='\r')
		{
			UARTCharPut(UART0_BASE,'\n');
		}		
	}
}
