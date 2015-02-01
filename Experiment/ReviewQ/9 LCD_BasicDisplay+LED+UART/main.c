#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"
#include "grlib/grlib.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"
#include "WatchDogConfigure.h"
#include "UARTConfigure.h"
#include "I2CConfigure.h"
#include "NixieTubeConfigure.h"
#include "PWMConfigure.h"
#include "LCDConfigure.h"
#include "LCDDisplay.h"

tContext sContext;
tRectangle sRect={0,39,319,239};

unsigned char SystemState=0;				//0-Normal 1-I2C Default
volatile unsigned char SystemActivatedFlag=false;

extern volatile unsigned char KeyNumber;	//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;

extern volatile unsigned char LCDDrawingFlag_Running;
extern volatile unsigned char LCDDrawingFlag_Pause;

volatile unsigned char SetFlag=0;			//0-ʱ��ģʽ 1-����ģʽ
volatile unsigned char SetBitFlag=0;		//0-������   1-���÷�

volatile unsigned char CounterSecond=0;
volatile unsigned char CounterMinute=0;

volatile unsigned char SetSecond=59;
volatile unsigned char SetMinute=59;
 	
int main(void)						//������
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();
	UART0Initial();
	GrContextInit(&sContext, &g_sKitronix320x240x16_SSD2119);
	LCDInitial();	
	PWMInitial();
	SystemState |= I2C0PullUpTest();
	if (!(SystemState & 0x01))	
		I2C0MasterInitial();
	sprintf(NixieTube,"CTM3 ");
	SysTickEnable();
	IntMasterEnable();
	LCDSystemCheckInformationDisplay(SystemState);
	UARTSystemCheckInformationTransmit(UART0_BASE,SystemState);

	LEDOn(LED_1);
	while (KeyNumber==0);	KeyNumber=0;
	LEDOff(LED_1);
	UARTStringPut(UART0_BASE,"System activated!\r\n");

/****************************Complete the code!!************************************/
//�ɸ���LCDDisplay.c�е����ӽ�������
	GrContextForegroundSet(&sContext, ClrBlack);	//��sRect����Ϳ�ɺ�ɫ
	GrRectFill(&sContext, &sRect);				//����Ļ�ϻ����ַ�
	GrContextForegroundSet(&sContext, ClrGold);	//�����ַ���ɫ
	GrContextFontSet(&sContext,&g_sFontCm14);			//�����ַ�����
	GrStringDrawCentered(&sContext, "Running", -1, GrContextDpyWidthGet(&sContext)/2,
						 GrContextDpyHeightGet(&sContext)/2, 1);		//����Ļ������ʾ��Running��
/**********************************************************************************/

/****************************Complete the code!!************************************/
	sprintf(NixieTube, "0000:");		//���ֹ����00��00
/**********************************************************************************/
	LEDOn(LED_1);	
	TimerEnable(TIMER0_BASE,TIMER_A);					
/****************************Complete the code!!************************************/
	BuzzerBeep(ALARM_SOUND_PERIOD,TheSysClock/5);//ʹ��BuzzerBeep����������ʱ������
/**********************************************************************************/
	SystemActivatedFlag=true;


	while(1)
	{	
		if (LCDDrawingFlag_Running)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext, ClrWhite);	//�����ַ���ɫ
			GrStringDrawCentered(&sContext, "Running", -1, GrContextDpyWidthGet(&sContext)/2,
						 		 GrContextDpyHeightGet(&sContext)/2, 1);		//����Ļ������ʾ�ַ���Running��
/**********************************************************************************/

			LCDDrawingFlag_Running=false;
		}
		if (LCDDrawingFlag_Pause)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext, ClrWhite);	//�����ַ���ɫ
			GrStringDrawCentered(&sContext, "  Pause  ", -1, GrContextDpyWidthGet(&sContext)/2,
						 		 GrContextDpyHeightGet(&sContext)/2, 1);		//����Ļ������ʾ�ַ���Pause�������ڸǵ��ַ���Running��
/**********************************************************************************/

			LCDDrawingFlag_Pause=false;
		}	
	}
}
