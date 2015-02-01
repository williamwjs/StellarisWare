#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysTickISR.h"

void SysTick_ISR(void)							//SysTick�жϺ���
{
	if (UARTSendFlag)
	{					 						//��ʱ����
		UARTCharPut(UART0_BASE,'\r');
		UARTCharPut(UART0_BASE,'\n');	
		UARTSendFlag=false;
	}
}
