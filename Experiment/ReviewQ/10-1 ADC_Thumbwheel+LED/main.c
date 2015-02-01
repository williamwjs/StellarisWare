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
#include "ADCConfigure.h"

tContext sContext;
tRectangle sRect={0,39,319,239};
char tMessage[40];

unsigned char SystemState=0;			//0-Normal 1-I2C Default
volatile unsigned char SystemActivatedFlag=0;

extern volatile unsigned char KeyNumber;			//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;

extern volatile unsigned char LCDDrawingFlag_Running;
extern volatile unsigned char LCDDrawingFlag_Pause;
extern volatile unsigned char LCDDrawingFlag_Thumbwheel;

extern unsigned long MeasureResult_Thumbwheel;

volatile unsigned char SetFlag=0;		//0-ʱ��ģʽ 1-����ģʽ
volatile unsigned char SetBitFlag=0;	

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
	ADCInitial();
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
	GrContextForegroundSet(&sContext, ClrBlack);	//��sRect����Ϳ�ɺ�ɫ
	GrRectFill(&sContext, &sRect);				//����Ļ�ϻ����ַ�
	GrContextForegroundSet(&sContext, ClrGold);	//�����ַ���ɫ
	GrContextFontSet(&sContext,&g_sFontCmss18i);			//�����ַ�����
	GrStringDrawCentered(&sContext, "Running", -1, GrContextDpyWidthGet(&sContext)/2,
						 130, 1);		//����Ļ������ʾ��Running��
/**********************************************************************************/

/****************************Complete the code!!************************************/
	//����Ļ�ϻ����ַ�"Thumbwheel Voltage:"��"mV"��"Adjustment Scale:"���ַ�
	GrContextForegroundSet(&sContext, ClrWhite);	//�����ַ���ɫ
	GrContextFontSet(&sContext,&g_sFontCmss18i);			//�����ַ�����
	GrStringDraw(&sContext, "Thumbwheel Voltage", -1, 15,LCD_THUMBWHEEL_LINE, 1);				//��(15,LCD_THUMBWHEEL_LINE��Ϊ���Ͻ�������ʾ�ַ���Thumbwheel Voltage��
	GrStringDraw(&sContext, "mV", -1, 280,LCD_THUMBWHEEL_LINE, 1);				//��(280,LCD_THUMBWHEEL_LINE��Ϊ���Ͻ�������ʾ�ַ���mV��
	GrStringDraw(&sContext, "Adjustment Scale:", -1, 15,LCD_SETBIT_LINE, 1);				//��(15,LCD_SETBIT_LINE��Ϊ���Ͻ�������ʾ�ַ���Adjustment Scale:��
/**********************************************************************************/

/****************************Complete the code!!************************************/
	sprintf(NixieTube, "0000:");		//���ֹ����00��00
/**********************************************************************************/
	LEDOn(LED_1);
	TimerEnable(TIMER0_BASE,TIMER_A);					
/****************************Complete the code!!************************************/
	BuzzerBeep(ALARM_SOUND_PERIOD,TheSysClock/5);				//ʹ��BuzzerBeep����������ʱ������
/**********************************************************************************/
	SystemActivatedFlag=1;

	while(1)
	{	
		if (LCDDrawingFlag_Running)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext, ClrWhite);	//�����ַ���ɫ
			GrContextFontSet(&sContext,&g_sFontCmss18i);			//�����ַ����� 	
			GrStringDrawCentered(&sContext, "Running", -1, GrContextDpyWidthGet(&sContext)/2,
						 		 130, 1);		//����Ļ������ʾ�ַ���Running��
/**********************************************************************************/
			LCDDrawingFlag_Running=false;
		}
		if (LCDDrawingFlag_Pause)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext, ClrWhite);	//�����ַ���ɫ
			GrContextFontSet(&sContext,&g_sFontCmss18i);			//�����ַ�����
			GrStringDrawCentered(&sContext, "  Pause  ", -1, GrContextDpyWidthGet(&sContext)/2,
						 		 130, 1);		//����Ļ������ʾ�ַ���Pause�������ڸǵ��ַ���Running��
/**********************************************************************************/
			LCDDrawingFlag_Pause=false;
		}
		if (LCDDrawingFlag_Thumbwheel)
		{
/****************************Complete the code!!************************************/
			sprintf(tMessage,"%4d ", (MeasureResult_Thumbwheel*3000)/1023);	//���ָ�ֵ�ѹ���㣬��������ַ���tMessage��
/***********************************************************************************/

/****************************Complete the code!!************************************/
			//����Ļ����ʾʵ��ָ�ֵ�ѹ
			GrContextForegroundSet(&sContext, ClrWhite);	//�����ַ���ɫ
			GrContextFontSet(&sContext,&g_sFontCmss18i);			//�����ַ�����
			GrStringDraw(&sContext, tMessage, -1, 220,LCD_THUMBWHEEL_LINE, 1);				//��(220,LCD_THUMBWHEEL_LINE��Ϊ���Ͻ�������ʾʵ��ָ�ֵ�ѹ���ѱ�������tMessage�У�
/**********************************************************************************/
			
			switch (MeasureResult_Thumbwheel/128)
			{
				case 0:
				{
					LEDSerial=0x00;
					break;
				}
				case 1:
				{
					LEDSerial=0x80;
					break;
				}
				case 2:
				{
					LEDSerial=0xC0;
					break;
				}
				case 3:
				{
					LEDSerial=0xE0;
					break;
				}
				case 4:
				{
					LEDSerial=0xF0;
					break;
				}
				case 5:
				{
					LEDSerial=0xF8;
					break;
				}
				case 6:
				{
					LEDSerial=0xFC;
					break;
				}
				case 7:
				{
					LEDSerial=0xFE;
					break;
				}
				default:
				{
					LEDSerial=0x00;
					break;
				}
			}

			switch (MeasureResult_Thumbwheel/256)
			{
				case 0:	
				{
					sprintf(tMessage," 1 Second  ");
					SetBitFlag=0;
					break;
				}
				case 1: 
				{
					sprintf(tMessage,"10 Seconds ");
					SetBitFlag=1;
					break;
				}
				case 2:
				{
					sprintf(tMessage," 1 Minute  ");
					SetBitFlag=2;
					break;
				}
				case 3:
				{
					sprintf(tMessage,"10 Minutes ");
					SetBitFlag=3;
					break;
				}
				default:
				{
					sprintf(tMessage," 1 Second  ");
					SetBitFlag=0;
					break;
				}
			}
			GrContextForegroundSet(&sContext, ClrCyan);
			GrStringDraw(&sContext, tMessage,-1,220,LCD_SETBIT_LINE,1);
			LCDDrawingFlag_Thumbwheel=false;
		}	
	}
}
