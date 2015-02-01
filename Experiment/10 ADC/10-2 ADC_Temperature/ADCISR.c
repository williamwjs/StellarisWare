#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "LCDDisplay.h"
#include "ADCConfigure.h"
#include "ADCISR.h"

void ADC_Sequence_0_ISR(void)
{
	unsigned long ulStatus;
	ulStatus=ADCIntStatus(ADC0_BASE,0,true);
	ADCIntClear(ADC0_BASE,0);
	if (ulStatus)
	{
/***********************Complete the Code**********************/
		ADCSequenceDataGet(ADC0_BASE,0,&MeasureResult_Thumbwheel);		//将采样序列获得的数据读入MeasureResult_Thumbwheel变量中
/**************************************************************/
		LCDDrawingFlag_Thumbwheel=true;	 
	}
}

void ADC_Sequence_1_ISR(void)
{
	unsigned long ulStatus;
	ulStatus=ADCIntStatus(ADC0_BASE,1,true);
	ADCIntClear(ADC0_BASE,1);
	if (ulStatus)
	{
/***********************Complete the Code**********************/
		ADCSequenceDataGet(ADC0_BASE,1,&MeasureResult_Temperature);		//将采样序列获得的数据读入MeasureResult_Temperature变量中
/**************************************************************/
		LCDDrawingFlag_Temperature=true;	 
	}
}
