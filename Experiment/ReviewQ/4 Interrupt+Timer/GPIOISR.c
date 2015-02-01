#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "GPIOISR.h"
#include "SysCtlConfigure.h"

void GPIO_Port_E_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTE_BASE,true);
	GPIOPinIntClear(GPIO_PORTE_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_5) //Press
	{
		if(ShiningEnable)
		{	
			SysTickDisable();
			TimerDisable(TIMER0_BASE,TIMER_A);
			ShiningEnable=false;
			LEDOff(LED_ALL);
		}
	}
	
	if (ulStatus & GPIO_PIN_4) //Up
	{
		if(!ShiningEnable)
		{
			TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock/2));	//TIMER0Aװ�ؼ���ֵ
			SysTickPeriodSet(TheSysClock/2);					//SysTick����ֵװ��
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			LEDOn(LED_ALL);
		}
	}
}

void GPIO_Port_B_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTB_BASE,true);
	GPIOPinIntClear(GPIO_PORTB_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_4) //Left
	{
		if(!ShiningEnable)
		{
			TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock/2));	//TIMER0Aװ�ؼ���ֵ
			SysTickPeriodSet(TheSysClock/4);					//SysTick����ֵװ��
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			LEDOn(LED_ALL);
		}
	}

	if (ulStatus & GPIO_PIN_6) //Right
	{
		if(!ShiningEnable)
		{
			TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock/4));	//TIMER0Aװ�ؼ���ֵ
			SysTickPeriodSet(TheSysClock/2);					//SysTick����ֵװ��
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			LEDOn(LED_ALL);
		}
	}
}
void GPIO_Port_F_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTF_BASE,true);
	GPIOPinIntClear(GPIO_PORTF_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_1) //Down
	{
		if(!ShiningEnable)
		{
			TimerLoadSet(TIMER0_BASE,TIMER_A,(TheSysClock/4));	//TIMER0Aװ�ؼ���ֵ
			SysTickPeriodSet(TheSysClock/4);					//SysTick����ֵװ��
			SysTickEnable();
			TimerEnable(TIMER0_BASE,TIMER_A);
			ShiningEnable=true;
			LEDOn(LED_ALL);
		}
	}
}

