#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "LCDDisplay.h"
#include "ADCConfigure.h"
#include "ADCISR.h"
#include "grlib/grlib.h"

int i = 0;

void ADC_Sequence_0_ISR(void)
{
	unsigned long ulStatus;
	ulStatus=ADCIntStatus(ADC0_BASE,0,true);
	ADCIntClear(ADC0_BASE,0);
	if (ulStatus)
	{
/****************************Complete the code!!************************************/
		ADCSequenceDataGet(ADC_BASE, 0, &MeasureResult_Thumbwheel); 		//将采样序列获得的数据读入MeasureResult_Thumbwheel变量中
/**********************************************************************************/
		LCDDrawingFlag_Thumbwheel=true;
		
		GrContextForegroundSet(&sContext, ClrBlack);	//将sRect区域涂成黑色
		GrRectFill(&sContext, &sRect);				//在屏幕上绘制字符
		GrContextForegroundSet(&sContext, ClrWhite);	//设置字符颜色
		for (i=0;i<319;i++)
		{
			//ssRect[i].sXMin=ssRect[i+1].sXMin-1;
			ssRect[i].sYMin=ssRect[i+1].sYMin;
			//ssRect[1].sXMax=ssRect[i+1].sXMin-1;
			ssRect[i].sYMax=ssRect[i+1].sYMin;
		}
		ssRect[319].sXMin=319;
		ssRect[319].sYMin=(200-MeasureResult_Thumbwheel/8);
		ssRect[319].sXMax=319;
		ssRect[319].sYMax=(200-MeasureResult_Thumbwheel/8);
		for(i=0;i<320;i++)
		{
			GrRectFill(&sContext,&ssRect[i]);
		}
		for(i=0;i<319;i++)
		{
			GrLineDraw(&sContext,i,ssRect[i].sYMin,i+1,ssRect[i+1].sYMin);
		}		 
	}
}
 	
