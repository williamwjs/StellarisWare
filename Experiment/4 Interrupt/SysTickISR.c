#include "GPIODriverConfigure.h"

#include "SysTickISR.h"

void SysTick_ISR(void)				//SysTick�жϺ���������Startup.S��extern��
{
	LEDOverturn(LED_0);
}							
