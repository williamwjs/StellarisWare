#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "GPIOISR.h"

void GPIO_Port_E_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTE_BASE,true);
	GPIOPinIntClear(GPIO_PORTE_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_5)
	{
		if(ShiningEnable)
		{	
			SysTickDisable();
			TimerDisable(TIMER0_BASE,TIMER_A);
			ShiningEnable=false;
			LEDOff(LED_ALL);
		}
	}
	
	if (ulStatus & GPIO_PIN_4)
	{
		if(!ShiningEnable)
		{
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			//LEDOn(LED_ALL);
		}
	}
}

void GPIO_Port_B_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTB_BASE,true);
	GPIOPinIntClear(GPIO_PORTB_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_4)
	{
		if(!ShiningEnable)
		{
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			//LEDOn(LED_ALL);
		}
	}

	if (ulStatus & GPIO_PIN_6)
	{
		if(!ShiningEnable)
		{
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			//LEDOn(LED_ALL);
		}
	}
}
void GPIO_Port_F_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTF_BASE,true);
	GPIOPinIntClear(GPIO_PORTF_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_1)
	{
		if(!ShiningEnable)
		{
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			//LEDOn(LED_ALL);
		}
	}
}

