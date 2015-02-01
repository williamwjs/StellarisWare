#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "GPIOISR.h"

void GPIO_Port_E_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTE_BASE,true);
	GPIOPinIntClear(GPIO_PORTE_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_4)
	{
		TranscodingStatus=3;	//Сдת��д����дתСд
		LEDOn(LED_ALL);
	}
} 
 
void GPIO_Port_B_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTB_BASE,true);
	GPIOPinIntClear(GPIO_PORTB_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_4)
	{
		TranscodingStatus=TRANSCODINGSTATUS_1;	//Сдת��д
		LEDOn(LED_1);
		LEDOff(LED_0);	
	}
	if (ulStatus & GPIO_PIN_6)
	{
		TranscodingStatus=TRANSCODINGSTATUS_2;	//��дתСд
		LEDOn(LED_0);
		LEDOff(LED_1);
	}
}

void GPIO_Port_F_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTF_BASE,true);
	GPIOPinIntClear(GPIO_PORTF_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_1)
	{
		TranscodingStatus=TRANSCODINGSTATUS_0;	//��ת��
		LEDOff(LED_ALL);	
	}
}
