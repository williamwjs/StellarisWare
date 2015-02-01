#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "WatchDogConfigure.h"
#include "GPIOISR.h"

void GPIO_Port_E_ISR(void)
{
	unsigned long ulStatus;

	ulStatus=GPIOPinIntStatus(GPIO_PORTE_BASE,true);
	GPIOPinIntClear(GPIO_PORTE_BASE,ulStatus);

	if (ulStatus & GPIO_PIN_5)
	{
		WatchDogFeed();
		LEDOn(LED_1);
		SysCtlDelay(TheSysClock/30);
		LEDOff(LED_1);	
	}
} 
