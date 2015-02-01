#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "ADCConfigure.h"

unsigned long MeasureResult_Thumbwheel=0;

void ADCInitial(void)
{
/****************************Complete the code!!************************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);				//SysCtl使能ADC0模块 
	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_500KSPS);				//设置ADC采样速率为500ksps
	HWREG(ADC0_BASE + ADC_O_CTL)=0x01;						//使用外置基准电压 
	ADCSequenceEnable(ADC_BASE, 0);							//使能采样序列0  
	ADCSequenceConfigure(ADC_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);						//采样序列配置：使用ADC0模块，使用0号序列，处理器触发采样，采样优先级为0	
	ADCSequenceStepConfigure(ADC_BASE, 0, 0, ADC_CTL_IE|ADC_CTL_END|ADC_CTL_CH10);		//采样步进设置：使用ADC0模块，使用0号序列，步值为0，根据电路图设置通道，
																						//设置队列结束选择、中断使能 
	ADCHardwareOversampleConfigure(ADC_BASE,64);		//使用ADC过采样功能
	ADCIntEnable(ADC_BASE, 0);							//ADC模块使能ADC序列0中断 
	IntEnable(INT_ADC0SS0);								//NVIC模块使能ADC序列0中断
/***********************************************************************************/ 
}
