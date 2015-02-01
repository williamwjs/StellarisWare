#include "inc/hw_memmap.h"		//��ַ�궨��			
#include "inc/hw_types.h"		//�������ͺ궨�壬�Ĵ������ʺ���	
#include "driverlib/debug.h"	//������	
#include "driverlib/gpio.h" 	//ͨ��IO�ں궨��	
#include "driverlib/sysctl.h"	//ϵͳ���ƺ궨��

/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	�͵�ƽ��Ч

�����
SW_1	JP43	PB6		Right
SW_2	JP41	PE5		Press
SW_3	JP42	PE4		Up
SW_4	JP44	PF1		Down
SW_5	JP45	PB4		Left
�͵�ƽ����
*/

int main(void)					
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);		//ʹ�ܶ˿�B
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);		//ʹ�ܶ˿�E
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//ʹ�ܶ˿�F

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,				//PF2,PF3����Ϊ2mA�������
						  GPIO_PIN_2 |
						  GPIO_PIN_3);								   
	GPIOPinWrite(GPIO_PORTF_BASE,						//LED0,LED0����
				 GPIO_PIN_2,
				 GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE,
				 GPIO_PIN_3,
				 GPIO_PIN_3);

	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,			 	//����PB6,PE5,PE4,PF1,PB4Ϊ����
						 GPIO_PIN_4 | 
						 GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,
						 GPIO_PIN_4 | 
						 GPIO_PIN_5);	
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,
						 GPIO_PIN_1);
		
	while(1)
	{
		if (((GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6)>>2) &
			  GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_4))==0)				//�����
		{
			GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);		//LED1��
			GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,~GPIO_PIN_3);		//LED0��
		}
		else
		{
			if (((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4)>>3) &
			 	  GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1))== 0)			//�ϻ���
			{
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);	//LED1��
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3);	//LED0��
			}
			else
			{
				if ((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5)>>5)==0)	//����
				 
					GPIOPinWrite(GPIO_PORTF_BASE,
								 GPIO_PIN_2 |
								 GPIO_PIN_3,
								 ~GPIO_PIN_2 &
								 ~GPIO_PIN_3);							//LED0��LED1��
				
				else	
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2 |
								 GPIO_PIN_3,
								 GPIO_PIN_2 |
								 GPIO_PIN_3);							//�ر�LED0��LED1
			}
		} 	 
	}							   
}
