#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"

int main(void)						
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();

	while(1)	
	{
		if (KeyPress(KEY_PRESS))
		{
			if (SysTickValueGet() > (TheSysClock/2))
				LEDOn(LED_0);
			else
				LEDOff(LED_0);
			
			if (TimerValueGet(TIMER0_BASE,TIMER_A) > (TheSysClock/6))
				LEDOn(LED_1);
			else
				LEDOff(LED_1);
		}
		else
			LEDOff(LED_ALL);
	}
}
