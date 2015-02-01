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
/****************************Complete the code!!************************************/
		ADCSequenceDataGet(ADC_BASE, 0, &MeasureResult_Thumbwheel); 		//���������л�õ����ݶ���MeasureResult_Thumbwheel������
/**********************************************************************************/
		LCDDrawingFlag_Thumbwheel=true;	 
	}
}
 	
