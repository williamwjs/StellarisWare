#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "ADCConfigure.h"

unsigned long MeasureResult_Thumbwheel=0;
unsigned long MeasureResult_Temperature=0;

void ADCInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);			//SysCtlʹ��ADC0ģ�� 
	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);			//����ADC��������Ϊ500ksps 
 	HWREG(ADC1_BASE + ADC_O_CTL)=0x01;					//ʹ�����û�׼��ѹ
	ADCHardwareOversampleConfigure(ADC1_BASE,64);		//ʹ��ADC����������

	ADCSequenceEnable(ADC1_BASE, 0);					//ʹ�ܲ�������0 
 	
	//�����������ã�ʹ��ADC0ģ�飬ʹ��0�����У������������������������ȼ�Ϊ0 
	ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_PROCESSOR, 0); 
 	//�����������ã�ʹ��ADC0ģ�飬ʹ��0�����У���ֵΪ0�����ݵ�·ͼ����ͨ����
	//���ö��н���ѡ���ж�ʹ�� 
	ADCSequenceStepConfigure(ADC1_BASE, 0, 0,
					  		 ADC_CTL_CH10 | 
        			  		 ADC_CTL_END | 
        			  		 ADC_CTL_IE); 
	ADCIntEnable(ADC1_BASE, 0);        					//ADCģ��ʹ��ADC����0�ж� 
	IntEnable(INT_ADC1SS0);         						//NVICģ��ʹ��ADC����0�ж� 

	ADCSequenceEnable(ADC1_BASE,1);						//ʹ�ܲ�������1

	//�����������ã�ʹ��ADC0ģ�飬ʹ��1�����У������������������������ȼ�Ϊ0 
	ADCSequenceConfigure(ADC1_BASE,1,ADC_TRIGGER_PROCESSOR,0);
 	//�����������ã�ʹ��ADC0ģ�飬ʹ��1�����У���ֵΪ0��ѡ���ڲ�����ͨ����
	//���ö��н���ѡ���ж�ʹ�� 
	ADCSequenceStepConfigure(ADC1_BASE,1,0,ADC_CTL_TS |
										   ADC_CTL_END |
										   ADC_CTL_IE);
	ADCIntEnable(ADC1_BASE, 1);							//ADCģ��ʹ��ADC����1�ж�
	IntEnable(INT_ADC1SS1);								//NVICģ��ʹ��ADC����1�ж�

}
