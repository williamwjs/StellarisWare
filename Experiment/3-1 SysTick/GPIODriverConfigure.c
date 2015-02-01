#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"

void GPIOInitial(void)
{
  	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  		//KEY RIGHT | KEY LEFT
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);		//KEY PRESS | KEY UP
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//KEY DOWN  | LED1 | LED0
		
	GPIOPinConfigure(GPIO_PF2_LED1);
	GPIOPinConfigure(GPIO_PF3_LED0);
	
	GPIOPinTypeGPIOOutput(LED0_BASE,LED0_PIN);			//Set LED0
	GPIOPinTypeGPIOOutput(LED1_BASE,LED1_PIN);			//Set LED1
	LEDOff(LED_ALL);

	GPIOPinTypeGPIOInput(KEY_PRESS_BASE, KEY_PRESS_PIN);//Set Key Press
	GPIOPinTypeGPIOInput(KEY_LEFT_BASE,  KEY_LEFT_PIN);	//Set Key Left
	GPIOPinTypeGPIOInput(KEY_RIGHT_BASE, KEY_RIGHT_PIN);//Set Key Right
	GPIOPinTypeGPIOInput(KEY_UP_BASE,    KEY_UP_PIN);	//Set Key Up
	GPIOPinTypeGPIOInput(KEY_DOWN_BASE,  KEY_DOWN_PIN);	//Set Key Down
}

void LEDOn(unsigned char LEDNum)
{
	switch (LEDNum)
	{
		case	LED_0:	HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=~LED0_PIN;break;
		case	LED_1:	HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=~LED1_PIN;break;
		case	LED_ALL:
		{
			HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=~LED0_PIN;
			HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=~LED1_PIN;
			break;
		}
		default:	break;
	}
}

void LEDOff(unsigned char LEDNum)
{
	switch (LEDNum)
	{
		case	LED_0:	HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=LED0_PIN;break;
		case	LED_1:	HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=LED1_PIN;break;
		case	LED_ALL:
		{
			HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2))=LED0_PIN;
			HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2))=LED1_PIN;
			break;
		}
		default:	break;
	}
}

void LEDOverturn(unsigned char LEDNum)
{
	switch (LEDNum)
	{
		case	LED_0:	HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2)) =
						~HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2));
						break;
		case	LED_1:	HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2)) =
						~HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2));
						break;
		case	LED_ALL:
		{
			HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2)) =
			~HWREG(LED0_BASE+GPIO_O_DATA+(LED0_PIN<<2));
			HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2)) =
			~HWREG(LED1_BASE+GPIO_O_DATA+(LED1_PIN<<2));
			break;
		}
		default:	break;
	}
}		

unsigned char KeyPress(unsigned char KeyNum)
{
	switch	(KeyNum)
	{
		case	KEY_PRESS:
		{
			if (HWREG(KEY_PRESS_BASE+GPIO_O_DATA+(KEY_PRESS_PIN<<2)))
				return 0;
			else
				return 1;
		}
		case	KEY_LEFT:
		{
			if (HWREG(KEY_LEFT_BASE+GPIO_O_DATA+(KEY_LEFT_PIN<<2)))
				return 0;
			else
				return 1;
		}
		case	KEY_RIGHT:
		{
			if (HWREG(KEY_RIGHT_BASE+GPIO_O_DATA+(KEY_RIGHT_PIN<<2)))
				return 0;
			else
				return 1;
		}
		case	KEY_UP:
		{
			if (HWREG(KEY_UP_BASE+GPIO_O_DATA+(KEY_UP_PIN<<2)))
				return 0;
			else
				return 1;
		}
		case	KEY_DOWN:
		{
			if (HWREG(KEY_DOWN_BASE+GPIO_O_DATA+(KEY_DOWN_PIN<<2)))
				return 0;
			else
				return 1;
		}
		default:	break;
	}
	return 0;
}


