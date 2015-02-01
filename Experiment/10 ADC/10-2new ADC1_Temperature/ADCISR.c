#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "LCDDisplay.h"
#include "ADCConfigure.h"
#include "ADCISR.h"

void ADC1_Sequence_0_ISR(void)
{
	unsigned long ulStatus;
	ulStatus=ADCIntStatus(ADC1_BASE,0,true);
	ADCIntClear(ADC1_BASE,0);
	if (ulStatus)
	{
		ADCSequenceDataGet(ADC1_BASE,0,&MeasureResult_Thumbwheel);
		LCDDrawingFlag_Thumbwheel=true;	 
	}
}

void ADC1_Sequence_1_ISR(void)
{
	unsigned long ulStatus;
	ulStatus=ADCIntStatus(ADC1_BASE,1,true);
	ADCIntClear(ADC1_BASE,1);
	if (ulStatus)
	{
		ADCSequenceDataGet(ADC1_BASE,1,&MeasureResult_Temperature);
		LCDDrawingFlag_Temperature=true;	 
	}
}
