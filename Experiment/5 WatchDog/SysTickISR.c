#include "SysTickISR.h"

void SysTick_ISR(void)							//SysTick�жϺ���
{
	BlinkFlag=1-BlinkFlag;	
}
