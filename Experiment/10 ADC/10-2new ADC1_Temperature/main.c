#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"
#include "grlib/grlib.h"			//图形库

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

volatile unsigned char SetFlag=0;		//0-时钟模式 1-设置模式
volatile unsigned char SetBitFlag=0;	

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

	GrContextForegroundSet(&sContext, ClrBlack);
	GrRectFill(&sContext,&sRect);
	GrContextForegroundSet(&sContext,ClrGreenYellow);
	GrContextFontSet(&sContext,&g_sFontCm40b);
	GrStringDrawCentered(&sContext,"Running",-1,
			GrContextDpyWidthGet(&sContext)/2,LCD_CLOCK_STATE_LINE,1);

	GrContextForegroundSet(&sContext, ClrSnow);
	GrContextFontSet(&sContext, &g_sFontCm18b);
	GrStringDraw(&sContext, "Thumbwheel Voltage:",-1,15,LCD_THUMBWHEEL_LINE,0);
	GrStringDraw(&sContext, "mV",-1,280,LCD_THUMBWHEEL_LINE,0);
	GrStringDraw(&sContext, "Adjustment Scale:",-1,15,LCD_SETBIT_LINE,0);
	GrStringDraw(&sContext, "Chip Temperature:",-1,15,LCD_TEMPERATURE_LINE,0);
	GrStringDraw(&sContext, "\'C",-1,280,LCD_TEMPERATURE_LINE,0);

	sprintf(NixieTube,"%04u:",CounterMinute*100+CounterSecond);
	LEDOn(LED_1);	

	TimerEnable(TIMER0_BASE,TIMER_A);					
	BuzzerBeep(ALARM_SOUND_PERIOD,TheSysClock/5);
	SystemActivatedFlag=true;


	while(1)
	{	
		if (LCDDrawingFlag_Running)
		{
			GrContextForegroundSet(&sContext,ClrGreenYellow);
			GrContextFontSet(&sContext,&g_sFontCm40b);
			GrStringDrawCentered(&sContext,"Running",-1,
					 			 GrContextDpyWidthGet(&sContext)/2,
					 			 LCD_CLOCK_STATE_LINE,1);
			LCDDrawingFlag_Running=false;
		}
		if (LCDDrawingFlag_Pause)
		{
			GrContextForegroundSet(&sContext,ClrOrange);
			GrContextFontSet(&sContext,&g_sFontCm40b);
			GrStringDrawCentered(&sContext,"  Pause  ",-1,
					 			 GrContextDpyWidthGet(&sContext)/2,
					 			 LCD_CLOCK_STATE_LINE,1);
			LCDDrawingFlag_Pause=false;
		}
		if (LCDDrawingFlag_Thumbwheel)
		{
			sprintf(tMessage,"%4d ",(MeasureResult_Thumbwheel*3000)/1023);	//完成指轮电压换算，并输出到字符串tMessage中
			GrContextForegroundSet(&sContext, ClrYellow);
			GrContextFontSet(&sContext, &g_sFontCm18b);
			GrStringDraw(&sContext, tMessage,-1,220,LCD_THUMBWHEEL_LINE,1);
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
			sprintf(tMessage,"%2.2f ",((float)(151040-225*MeasureResult_Temperature)/1024));//完成温度换算，并输出到字符串tMessage中
			GrContextForegroundSet(&sContext, ClrRed);
			GrContextFontSet(&sContext, &g_sFontCm18b);
			GrStringDraw(&sContext, tMessage,-1,220,LCD_TEMPERATURE_LINE,1);
			LCDDrawingFlag_Temperature=false;
		}	
	}
}
