#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "ADCConfigure.h"

unsigned long MeasureResult_Thumbwheel=0;
unsigned long MeasureResult_Temperature=0;

void ADCInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);			//SysCtl使能ADC0模块 
	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);			//设置ADC采样速率为500ksps 
 	HWREG(ADC1_BASE + ADC_O_CTL)=0x01;					//使用外置基准电压
	ADCHardwareOversampleConfigure(ADC1_BASE,64);		//使用ADC过采样功能

	ADCSequenceEnable(ADC1_BASE, 0);					//使能采样序列0 
 	
	//采样序列配置：使用ADC0模块，使用0号序列，处理器触发采样，采样优先级为0 
	ADCSequenceConfigure(ADC1_BASE, 0, ADC_TRIGGER_PROCESSOR, 0); 
 	//采样步进设置：使用ADC0模块，使用0号序列，步值为0，根据电路图设置通道，
	//设置队列结束选择、中断使能 
	ADCSequenceStepConfigure(ADC1_BASE, 0, 0,
					  		 ADC_CTL_CH10 | 
        			  		 ADC_CTL_END | 
        			  		 ADC_CTL_IE); 
	ADCIntEnable(ADC1_BASE, 0);        					//ADC模块使能ADC序列0中断 
	IntEnable(INT_ADC1SS0);         						//NVIC模块使能ADC序列0中断 

	ADCSequenceEnable(ADC1_BASE,1);						//使能采样序列1

	//采样序列配置：使用ADC0模块，使用1号序列，处理器触发采样，采样优先级为0 
	ADCSequenceConfigure(ADC1_BASE,1,ADC_TRIGGER_PROCESSOR,0);
 	//采样步进设置：使用ADC0模块，使用1号序列，步值为0，选择内部测温通道，
	//设置队列结束选择、中断使能 
	ADCSequenceStepConfigure(ADC1_BASE,1,0,ADC_CTL_TS |
										   ADC_CTL_END |
										   ADC_CTL_IE);
	ADCIntEnable(ADC1_BASE, 1);							//ADC模块使能ADC序列1中断
	IntEnable(INT_ADC1SS1);								//NVIC模块使能ADC序列1中断

}
