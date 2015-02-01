#include "inc/hw_memmap.h"		//��ַ�궨��			
#include "inc/hw_types.h"		//�������ͺ궨�壬�Ĵ������ʺ���	
#include "driverlib/debug.h"	//������	
#include "driverlib/gpio.h" 	//ͨ��IO�ں궨��	
#include "driverlib/sysctl.h"	//ϵͳ���ƺ궨��			

/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	�͵�ƽ��Ч
*/

int main(void)						
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//ʹ�ܶ˿ڣ�����յȴ���䣩	
	GPIODirModeSet(GPIO_PORTF_BASE,						//����Ϊ���
				   GPIO_PIN_2 | 
				   GPIO_PIN_3,
				   GPIO_DIR_MODE_OUT);
	GPIOPadConfigSet(GPIO_PORTF_BASE,					//����Ϊ8mA����ת�����ʿ��Ƶ��������
					 GPIO_PIN_2 | 
					 GPIO_PIN_3,
					 GPIO_STRENGTH_8MA_SC,
					 GPIO_PIN_TYPE_STD);
	/*�������ã�
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
						  GPIO_PIN_2 |
						  GPIO_PIN_3);	//����Ϊ2mA�������
	*/						   
	GPIOPinWrite(GPIO_PORTF_BASE,						//����LED1
				 GPIO_PIN_2,
				 ~GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE,						//����LED0
				 GPIO_PIN_3,
				 ~GPIO_PIN_3);
	while(1);
}
