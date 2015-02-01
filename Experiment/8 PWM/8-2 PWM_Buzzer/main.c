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
#include "PWMConfigure.h"

unsigned char SystemState=0;			//0-Normal 1-I2C Default

extern volatile unsigned char KeyNumber;		//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;

extern char NixieTube[];
extern unsigned char volatile LEDSerial;

volatile unsigned char SetFlag=0;		//0-时钟模式 1-设置模式
volatile unsigned char SetBitFlag=0;	//0-设置秒   1-设置分

volatile unsigned char CounterSecond=0;
volatile unsigned char CounterMinute=0;

volatile unsigned char SetSecond=59;
volatile unsigned char SetMinute=59;
	
int main(void)						//主函数
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();
	UART0Initial();
	PWMInitial();
	SystemState |= I2C0PullUpTest();
	if (!(SystemState & 0x01))	I2C0MasterInitial();
	sprintf(NixieTube,"CTM3 ");								
	UARTSystemCheckInformationTransmit(UART0_BASE,SystemState);
	SysTickEnable();
	IntMasterEnable();																
				
	LEDOn(LED_1);
	while (KeyNumber==0);	KeyNumber=0;
	LEDOff(LED_1);
	UARTStringPut(UART0_BASE,"System activated!\r\n");

/****************************Complete the code!!************************************/
	sprintf(NixieTube, "0000:");		//米字冠输出00：00
/**********************************************************************************/
	LEDOn(LED_1);
/****************************Complete the code!!************************************/
	BuzzerBeep(ALARM_SOUND_PERIOD,(TheSysClock/5));//使用BuzzerBeep函数发出短时报警音
/**********************************************************************************/
	TimerEnable(TIMER0_BASE,TIMER_A);					//打开TIMER0

	while(1)
	{	
		if (KeyNumber==1)
		{
			if (SetFlag==0)
			{
/****************************Complete the code!!************************************/
				sprintf(NixieTube,"%04u:", SetMinute*100+SetSecond);//米字管输出设置时间
/**********************************************************************************/
				SetFlag=1;
/****************************Complete the code!!************************************/
				BuzzerBeep(SET_SOUND_PERIOD,(TheSysClock/5));//使用BuzzerBeep函数发出短时设置音
/**********************************************************************************/
				TimerDisable(TIMER0_BASE,TIMER_A);
			}
			else
			{
/****************************Complete the code!!************************************/
				sprintf(NixieTube,"%04u:", CounterMinute*100+CounterSecond);	//米字管输出计时时间
/**********************************************************************************/
				SetFlag=0;
				SetBitFlag=0;
/****************************Complete the code!!************************************/
				BuzzerBeep(SET_SOUND_PERIOD,(TheSysClock/5));//使用BuzzerBeep函数发出短时设置音
/**********************************************************************************/
				TimerEnable(TIMER0_BASE,TIMER_A);
			}
			LEDOverturn(LED_1);
			KeyNumber=0;
		}

		if (KeyNumber==4 && SetFlag==1) 	//上
		{
			if (SetBitFlag)
			{
				SetMinute++;
				if (SetMinute==60)	SetMinute=0;
			}
			else
			{
				SetSecond++;
				if (SetSecond==60) SetSecond=0;
			}
			KeyNumber=0;
/****************************Complete the code!!************************************/
			sprintf(NixieTube,"%04u:", SetMinute*100+SetSecond);		//米字冠输出设置时间
/**********************************************************************************/
		}
		
		if (KeyNumber==5 && SetFlag==1) 	//下
		{
			if (SetBitFlag)
			{
				if (SetMinute>0)	SetMinute--;
				else	SetMinute=59;
			}
			else
			{
				if (SetSecond>0) SetSecond--;
				else	SetSecond=59;
			}
			KeyNumber=0;
/****************************Complete the code!!************************************/
			sprintf(NixieTube,"%04u:", SetMinute*100+SetSecond);		//米字冠输出设置时间
/**********************************************************************************/
		}
		
		if ((KeyNumber==2 || KeyNumber==3)&& SetFlag==1) 	//左或右
		{
			SetBitFlag=1-SetBitFlag;
			KeyNumber=0;
		}
	}
}
