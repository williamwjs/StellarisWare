#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysTickISR.h"

void SysTick_ISR(void)							//SysTick中断函数
{
	if (UARTSendFlag)
	{					 						//定时换行
		UARTCharPut(UART0_BASE,'\r');
		UARTCharPut(UART0_BASE,'\n');	
		UARTSendFlag=false;
	}
}
