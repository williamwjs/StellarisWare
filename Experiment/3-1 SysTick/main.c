#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"

int main(void)						//Ö÷º¯Êý
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();

	while(1)	
	{
		if ( KeyPress(KEY_PRESS) &
			(SysTickValueGet() > (TheSysClock/2)))
		{
			LEDOn(LED_1);
			LEDOff(LED_0);
		}
		else
		{
			if ( KeyPress(KEY_PRESS) &
				(SysTickValueGet() <= (TheSysClock/2)))
			{
				LEDOn(LED_0);
				LEDOff(LED_1);
			}
			else	LEDOff(LED_ALL);
		}
	}
}
