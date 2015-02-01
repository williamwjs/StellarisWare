#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"
#include "WatchDogConfigure.h"
#include "UARTConfigure.h"
#include "I2CConfigure.h"
#include "NixieTubeConfigure.h"

unsigned char SystemState=0;				//0-Normal 1-I2C Default

extern volatile unsigned char KeyNumber;	//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;

extern char NixieTube[];
extern unsigned char volatile LEDSerial;

volatile unsigned char SetFlag=0;			//0-ʱ��ģʽ 1-����ģʽ
volatile unsigned char SetBitFlag=0;		//0-������   1-���÷�

volatile int CounterSecond=0;
volatile int CounterMinute=0;

volatile int SetSecond=59;
volatile int SetMinute=59;
int s1,s2;
 	
int main(void)						//������
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();
	UART0Initial();
	SystemState |= I2C0PullUpTest();
	if (!(SystemState & 0x01))	I2C0MasterInitial();
	sprintf(NixieTube,"CTM3 ");
	UARTSystemCheckInformationTransmit(UART0_BASE,SystemState);
	SysTickEnable();
	IntMasterEnable();								
				
	LEDOn(LED_ALL);
	while (KeyNumber==0);	KeyNumber=0;
	LEDOff(LED_1);
	UARTStringPut(UART0_BASE,"System activated!\r\n");
/****************************Complete the code!!************************************/
	sprintf(NixieTube, "0000:");		//���ֹ����00��00
/**********************************************************************************/

	TimerEnable(TIMER0_BASE,TIMER_A);					//��TIMER0

	while(1)
	{	
		if (KeyNumber==1)
		{
			if (SetFlag==0)
			{
/****************************Complete the code!!************************************/
				sprintf(NixieTube,"%04d:", SetMinute*100+SetSecond);//���ֹ��������ʱ��
/**********************************************************************************/
				SetFlag=1;
				TimerDisable(TIMER0_BASE,TIMER_A);
			}
			else
			{
/****************************Complete the code!!************************************/
				sprintf(NixieTube,"%04d:", CounterMinute*100+CounterSecond);	//���ֹ������ʱʱ��
/**********************************************************************************/
				SetFlag=0;
				SetBitFlag=0;
				TimerEnable(TIMER0_BASE,TIMER_A);
			}
			LEDOverturn(LED_ALL);
			KeyNumber=0;
		}

		if (KeyNumber==4 && SetFlag==1) 	//��
		{
			SetSecond++;
			if (SetSecond>59 && SetMinute<59) { SetMinute++; SetSecond=0; }
			if (SetSecond>59 && SetMinute>=59) { SetSecond=59; SetMinute=59; }  
			
			KeyNumber=0;
/****************************Complete the code!!************************************/
			sprintf(NixieTube,"%04d:", SetMinute*100+SetSecond);		//���ֹ��������ʱ��
/**********************************************************************************/
		}
		
		if (KeyNumber==5 && SetFlag==1) 	//��
		{
			SetSecond--; 
			if (SetSecond<0 && SetMinute>0) { SetMinute--; SetSecond=59; }
			if (SetSecond<0 && SetMinute<=0) { SetSecond=0; SetMinute=0; }

			KeyNumber=0;
/****************************Complete the code!!************************************/
			sprintf(NixieTube,"%04d:", SetMinute*100+SetSecond);		//���ֹ��������ʱ��
/**********************************************************************************/
		}
		
		if (KeyNumber==2 && SetFlag==1) 	//��
		{
			s1=SetMinute;
			s2=SetSecond;
			SetMinute = (s1%10)*10+s2/10;
			SetSecond = (s2%10)*10+s1/10;
			sprintf(NixieTube,"%04d:", SetMinute*100+SetSecond);		//���ֹ��������ʱ��
			KeyNumber=0;	  
		}
					   
		if (KeyNumber==3 && SetFlag==1) 	//��
		{
			s1=SetMinute;
			s2=SetSecond;
			SetMinute = (s2%10)*10+s1/10;
			SetSecond = (s1%10)*10+s2/10;
			sprintf(NixieTube,"%04d:", SetMinute*100+SetSecond);		//���ֹ��������ʱ��
			KeyNumber=0;	  
		}
	}
}
