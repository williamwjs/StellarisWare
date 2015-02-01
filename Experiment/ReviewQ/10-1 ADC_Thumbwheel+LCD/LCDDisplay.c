#include <stdio.h>
#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"
#include "grlib/grlib.h"

#include "SysCtlConfigure.h"
#include "GPIODriverConfigure.h"
#include "LCDConfigure.h"
#include "LCDDisplay.h"

volatile unsigned char LCDDrawingFlag_Running=false;
volatile unsigned char LCDDrawingFlag_Pause=false;
volatile unsigned char LCDDrawingFlag_Thumbwheel=false;

tRectangle ssRect[320];

void LCDSystemCheckInformationDisplay(unsigned char tSystemState)
{
	tContext tempContext;
	tRectangle tempRect={0,0,319,35};
	char tempMessage[40];
	int i = 0;

	GrContextInit(&tempContext, &g_sKitronix320x240x16_SSD2119);
	GrContextForegroundSet(&tempContext,ClrDarkBlue);
	GrContextBackgroundSet(&tempContext,ClrBlack);
	GrRectFill(&tempContext,&tempRect);

	GrContextForegroundSet(&tempContext,ClrGold);
	GrRectDraw(&tempContext,&tempRect);

	GrContextForegroundSet(&tempContext, ClrGold);
	GrContextFontSet(&tempContext, &g_sFontCmss18i);				
	GrStringDrawCentered(&tempContext, "ARM  Cortex-M3  Processing  System", -1,
                         GrContextDpyWidthGet(&tempContext) / 2,
                         GrStringHeightGet(&tempContext)-3,0);
	GrContextForegroundSet(&tempContext, ClrSnow);
	GrContextFontSet(&tempContext, &g_sFontCm14);
	GrStringDraw(&tempContext, "ARM Microcontroller Model:",    -1,5  ,48, 0);
	GrStringDraw(&tempContext, "Stellaris LM3S9B92",            -1,195,48, 0);
	GrStringDraw(&tempContext, "Manufacturer:",                 -1,5  ,63, 0);
	GrStringDraw(&tempContext, "Texas Instruments",             -1,195,63, 0);
	GrStringDraw(&tempContext, "Crystal Oscillator Frequencey:",-1,5,  78, 0);
	GrStringDraw(&tempContext, "16000000 Hz",                   -1,195,78, 0);
	GrStringDraw(&tempContext, "Main Clock Frequencey:",        -1,5,  93, 0);
	sprintf(tempMessage,"%d Hz",TheSysClock);
	GrStringDraw(&tempContext, tempMessage,                     -1,195,93, 0);
	GrStringDraw(&tempContext, "LCD Voltage:",                  -1,5,  108,0);
	if (SysCtlLDOGet()<0x10)
		sprintf(tempMessage,"%d mV",(2500-SysCtlLDOGet()*50));
	else
		sprintf(tempMessage,"%d mV",(2500+(0x20-SysCtlLDOGet())*50));
	GrStringDraw(&tempContext, tempMessage,                     -1,195,108,0);
	GrStringDraw(&tempContext, "Flash Size:",                   -1,5,  123,0);
	sprintf(tempMessage,"%d Bytes",SysCtlFlashSizeGet());
	GrStringDraw(&tempContext, tempMessage,                     -1,195,123,0);
	GrStringDraw(&tempContext, "SRAM Size:",                    -1,5,  138,0);
	sprintf(tempMessage,"%d Bytes",SysCtlSRAMSizeGet());
	GrStringDraw(&tempContext, tempMessage,                     -1,195,138,0);
	GrStringDraw(&tempContext, "Initial Done.",                 -1,5,  153,0);

	if (tSystemState & 0x01)
	{
		GrContextForegroundSet(&tempContext, ClrRed);
    	GrContextFontSet(&tempContext, &g_sFontCm20b);
    	GrStringDrawCentered(&tempContext, "I2C Pull-up Device Down", -1,
        	                 GrContextDpyWidthGet(&tempContext) / 2,183,0);
	}
	if (!tSystemState)
	{			
		GrContextForegroundSet(&tempContext, ClrLightGreen);
    	GrContextFontSet(&tempContext, &g_sFontCm20b);
    	GrStringDrawCentered(&tempContext, "System All Green", -1,
         	                GrContextDpyWidthGet(&tempContext) / 2,183,0);
	}

    GrContextFontSet(&tempContext, &g_sFontCmsc20);
	GrContextForegroundSet(&tempContext, ClrRed);
	GrStringDrawCentered(&tempContext, "Press the Key to Continue", -1,
                         GrContextDpyWidthGet(&tempContext) / 2,213,0);
						 
	for(i=0;i<320;i++)
	{
		ssRect[i].sXMin=i;
		ssRect[i].sYMin=200;
		ssRect[i].sXMax=i;
		ssRect[i].sYMax=200;
	}	
}
