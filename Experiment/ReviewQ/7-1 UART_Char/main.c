#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"
#include "WatchDogConfigure.h"
#include "UARTConfigure.h"
#include "I2CConfigure.h"

unsigned char SystemState=0;				//0-Normal 1-I2C Default

extern volatile unsigned char KeyNumber;
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;
 	
int main(void)						//������
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();
	UART0Initial();
	SystemState |= I2C0PullUpTest();
	if (!(SystemState & 0x01))	I2C0MasterInitial();
	UARTSystemCheckInformationTransmit(UART0_BASE,SystemState);
	SysTickEnable();								
									
	LEDOn(LED_ALL);
	while (!KeyNumber);
	LEDOff(LED_ALL);
	UARTStringPut(UART0_BASE,"System activated!\r\n");

	IntMasterEnable();
	TimerEnable(TIMER0_BASE,TIMER_A);					//��TIMER0

	while(1)
	{
/****************************Put your code here!!************************************/
		/*
			ʵ�ֹ��ܣ�ʹ��I2CMasterTransmit_Burst_2Bytes������I2C�����ϵ�7��LED�ƽ��б��
			�������PRESS������ʱ����һ��LED�Ƶ���
			�������LEFT������ʱ���ڶ���LED�Ƶ���
			�������RIGHT������ʱ��������LED�Ƶ���
			�������UP������ʱ�����ĸ�LED�Ƶ���
			�������DOWN������ʱ�������LED�Ƶ���
		*/
		/*
		switch (GetKeyNumber())
		{
			case	KEY_PRESS:	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x02);
								break;
			case	KEY_LEFT:	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x04);
								break;
			case	KEY_RIGHT:	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x08);
								break;
			case	KEY_UP:		I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x10);
								break;
			case	KEY_DOWN:	I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x20);
								break;
			default:			break;			
		}
		*/
	
		if(KeyNumber)
		{
			I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x01<<KeyNumber);
		}
		else
		{
			I2CMasterTransmit_Burst_2Bytes(I2C0_MASTER_BASE,LED_I2CADDR,PCA9557_REG_OUTPUT,0x00);
		}	
/************************************************************************************/		
	}
}
