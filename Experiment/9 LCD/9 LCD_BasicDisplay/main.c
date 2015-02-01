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

volatile unsigned char SetFlag=0;			//0-时钟模式 1-设置模式
volatile unsigned char SetBitFlag=0;		//0-设置秒   1-设置分

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
//可根据LCDDisplay.c中的例子进行配置
	GrContextForegroundSet(&sContext, ClrBlack);	//将sRect区域涂成黑色
	GrRectFill(&sContext, &sRect);				//在屏幕上绘制字符
	GrContextForegroundSet(&sContext, ClrGold);	//设置字符颜色
	GrContextFontSet(&sContext,&g_sFontCm14);			//设置字符字体
	GrStringDrawCentered(&sContext, "Running", -1, GrContextDpyWidthGet(&sContext)/2,
						 GrContextDpyHeightGet(&sContext)/2, 1);		//在屏幕正中显示“Running”
/**********************************************************************************/

/****************************Complete the code!!************************************/
	sprintf(NixieTube, "0000:");		//米字冠输出00：00
/**********************************************************************************/
	LEDOn(LED_1);	
	TimerEnable(TIMER0_BASE,TIMER_A);					
/****************************Complete the code!!************************************/
	BuzzerBeep(ALARM_SOUND_PERIOD,TheSysClock/5);//使用BuzzerBeep函数发出短时报警音
/**********************************************************************************/
	SystemActivatedFlag=true;


	while(1)
	{	
		if (LCDDrawingFlag_Running)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext, ClrWhite);	//设置字符颜色
			GrStringDrawCentered(&sContext, "Running", -1, GrContextDpyWidthGet(&sContext)/2,
						 		 GrContextDpyHeightGet(&sContext)/2, 1);		//在屏幕正中显示字符“Running”
/**********************************************************************************/

			LCDDrawingFlag_Running=false;
		}
		if (LCDDrawingFlag_Pause)
		{
/****************************Complete the code!!************************************/
			GrContextForegroundSet(&sContext, ClrWhite);	//设置字符颜色
			GrStringDrawCentered(&sContext, "  Pause  ", -1, GrContextDpyWidthGet(&sContext)/2,
						 		 GrContextDpyHeightGet(&sContext)/2, 1);		//在屏幕正中显示字符“Pause”，并遮盖掉字符“Running”
/**********************************************************************************/

			LCDDrawingFlag_Pause=false;
		}	
	}
}
