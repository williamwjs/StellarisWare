#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"
#include "grlib/grlib.h"			//ͼ�ο�

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
volatile unsigned char SystemActivatedFlag=false;

extern volatile unsigned char KeyNumber;			//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;

extern volatile unsigned char LCDDrawingFlag_Running;
extern volatile unsigned char LCDDrawingFlag_Pause;
extern volatile unsigned char LCDDrawingFlag_Thumbwheel;
extern volatile unsigned char LCDDrawingFlag_Temperature;

extern unsigned long MeasureResult_Thumbwheel;
extern unsigned long MeasureResult_Temperature;

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
	GrRectFill(&sContext,&sRect);				//����Ļ�ϻ����ַ�"Running"
	GrContextForegroundSet(&sContext,ClrGreenYellow);	//�����ַ���ɫ
	GrContextFontSet(&sContext,&g_sFontCm40b);			//�����ַ�����
	GrStringDrawCentered(&sContext,"Running",-1,
			GrContextDpyWidthGet(&sContext)/2,LCD_CLOCK_STATE_LINE,1);		//����Ļ�ײ�������ʾ��Running��
/**********************************************************************************/

/****************************Complete the code!!************************************/
	//����Ļ�ϻ����ַ�"Thumbwheel Voltage:"��"mV"��"Adjustment Scale:"���ַ�
	GrContextForegroundSet(&sContext, ClrSnow);	//�����ַ���ɫ
	GrContextFontSet(&sContext, &g_sFontCm18b);			//�����ַ�����
	GrStringDraw(&sContext, "Thumbwheel Voltage:",-1,15,LCD_THUMBWHEEL_LINE,0);				//��(15,LCD_THUMBWHEEL_LIN��Ϊ���Ͻ�������ʾ�ַ���Thumbwheel Voltage��
	GrStringDraw(&sContext, "mV",-1,280,LCD_THUMBWHEEL_LINE,0);				//��(280,LCD_THUMBWHEEL_LIN��Ϊ���Ͻ�������ʾ�ַ���mV��
	GrStringDraw(&sContext, "Adjustment Scale:",-1,15,LCD_SETBIT_LINE,0);				//��(15,LCD_SETBIT_LINE��Ϊ���Ͻ�������ʾ�ַ���Adjustment Scale:��
	GrStringDraw(&sContext, "Chip Temperature:",-1,15,LCD_TEMPERATURE_LINE,0);
	GrStringDraw(&sContext, "\'C",-1,280,LCD_TEMPERATURE_LINE,0);
/**********************************************************************************/

/****************************Complete the code!!************************************/
	sprintf(NixieTube,"%04u:",CounterMinute*100+CounterSecond );		//���ֹ����00��00
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
			GrContextForegroundSet(&sContext,ClrGreenYellow);	//�����ַ���ɫ
			GrContextFontSet(&sContext,&g_sFontCm40b);			//�����ַ����� 	
			GrStringDrawCentered(&sContext,"Running",-1,
					 			 GrContextDpyWidthGet(&sContext)/2,
					 			 LCD_CLOCK_STATE_LINE,1);		//����Ļ�ײ�������ʾ�ַ���Running��
/**********************************************************************************/
			LCDDrawingFlag_Running=false;
		}
		if (LCDDrawingFlag_Pause)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext,ClrOrange);	//�����ַ���ɫ
			GrContextFontSet(&sContext,&g_sFontCm40b);			//�����ַ�����
			GrStringDrawCentered(&sContext,"  Pause  ",-1,
					 			 GrContextDpyWidthGet(&sContext)/2,
					 			 LCD_CLOCK_STATE_LINE,1);		//����Ļ������ʾ�ַ���Pause�������ڸǵ��ַ���Running��
/**********************************************************************************/
			LCDDrawingFlag_Pause=false;
		}
		if (LCDDrawingFlag_Thumbwheel)
		{
/****************************Complete the code!!************************************/
			sprintf(tMessage,"%4d ",(MeasureResult_Thumbwheel*3000)/1023 );	//���ָ�ֵ�ѹ���㣬��������ַ���tMessage��
/***********************************************************************************/

/****************************Complete the code!!************************************/
			//����Ļ����ʾʵ��ָ�ֵ�ѹ
			GrContextForegroundSet(&sContext, ClrYellow);	//�����ַ���ɫ
			GrContextFontSet(&sContext, &g_sFontCm18b);			//�����ַ�����
			GrStringDraw(&sContext, tMessage,-1,220,LCD_THUMBWHEEL_LINE,1);				//��(220,LCD_THUMBWHEEL_LIN��Ϊ���Ͻ�������ʾʵ��ָ�ֵ�ѹ���ѱ�������tMessage�У�
/**********************************************************************************/
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
					sprintf(tMessage," 1 Minute " );
					SetBitFlag=2;
					break;
				}
				case 3:
				{
					sprintf(tMessage,"10 Minutes");
					SetBitFlag=3;
					break;
				}
				default:
				{
					sprintf(tMessage," 1 Second ");
					SetBitFlag=0;
					break;
				}
			}
			GrContextForegroundSet(&sContext, ClrCyan);
			GrStringDraw(&sContext, tMessage,-1,220,LCD_SETBIT_LINE,1);
			LCDDrawingFlag_Thumbwheel=false;
		}																			 
		if (LCDDrawingFlag_Temperature)
		{
/****************************Complete the code!!************************************/
			sprintf(tMessage,"%2.2f ",(float)( 151040-225*MeasureResult_Temperature)/1024      );	//����¶Ȼ��㣬��������ַ���tMessage��
/***********************************************************************************/
/****************************Complete the code!!************************************/
			//����Ļ����ʾʵ���¶�
			GrContextForegroundSet(&sContext, ClrRed);		//�����ַ���ɫ
			GrContextFontSet(&sContext, &g_sFontCm18b);				//�����ַ�����
			GrStringDraw(&sContext, tMessage,-1,220,LCD_TEMPERATURE_LINE,1);					//��(220,LCD_TEMPERATURE_LINE��Ϊ���Ͻ�������ʾʵ���¶ȣ��ѱ�������tMessage�У�
/**********************************************************************************/
			LCDDrawingFlag_Temperature=false;
		}	
	}
}