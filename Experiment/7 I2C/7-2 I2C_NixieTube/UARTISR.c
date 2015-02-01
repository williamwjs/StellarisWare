#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"
#include "UARTISR.h"

void UART0_ISR(void)
{
	unsigned char receiveChar;
	unsigned long ulStatus;
	
	ulStatus=UARTIntStatus(UART0_BASE,true);
	UARTIntClear(UART0_BASE,ulStatus);
	
	if ((ulStatus &	UART_INT_RX)||(ulStatus & UART_INT_RT))
	{
		receiveChar=UARTCharGetNonBlocking(UART0_BASE);
		if (receiveChar=='S' || receiveChar=='s')		//按下S或s暂停		
			TimerDisable(TIMER0_BASE,TIMER_A);
		if (receiveChar=='R' || receiveChar=='r')		//按下R或r启动
			TimerEnable(TIMER0_BASE,TIMER_A);		 
	}	
}
