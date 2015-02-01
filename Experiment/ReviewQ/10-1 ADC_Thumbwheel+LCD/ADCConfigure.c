#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "ADCConfigure.h"

unsigned long MeasureResult_Thumbwheel=0;

void ADCInitial(void)
{
/****************************Complete the code!!************************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);				//SysCtlʹ��ADC0ģ�� 
	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);				//����ADC��������Ϊ500ksps
	HWREG(ADC0_BASE + ADC_O_CTL)=0x01;						//ʹ�����û�׼��ѹ 
	ADCSequenceEnable(ADC_BASE, 0);							//ʹ�ܲ�������0  
	ADCSequenceConfigure(ADC_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);						//�����������ã�ʹ��ADC0ģ�飬ʹ��0�����У������������������������ȼ�Ϊ0	
	ADCSequenceStepConfigure(ADC_BASE, 0, 0, ADC_CTL_IE|ADC_CTL_END|ADC_CTL_CH10);		//�����������ã�ʹ��ADC0ģ�飬ʹ��0�����У���ֵΪ0�����ݵ�·ͼ����ͨ����
																						//���ö��н���ѡ���ж�ʹ�� 
	ADCHardwareOversampleConfigure(ADC_BASE,64);		//ʹ��ADC����������
	ADCIntEnable(ADC_BASE, 0);							//ADCģ��ʹ��ADC����0�ж� 
	IntEnable(INT_ADC0SS0);								//NVICģ��ʹ��ADC����0�ж�
/***********************************************************************************/ 
}
