#include "SysTickISR.h"

void SysTick_ISR(void)							//SysTickÖÐ¶Ïº¯Êý
{
	BlinkFlag=1-BlinkFlag;	
}
