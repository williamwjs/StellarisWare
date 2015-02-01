#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "LCDDisplay.h"
#include "UARTISR.h"

void UART0_ISR(void)
{
	unsigned char receiveChar;
	unsigned long ulStatus;
	
	ulStatus=UARTIntStatus(UART0_BASE,true);
	UARTIntClear(UART0_BASE,ulStatus);
	
	if (!SystemActivatedFlag)	return;
	if ((ulStatus &	UART_INT_RX)||(ulStatus & UART_INT_RT))
	{
		receiveChar=UARTCharGetNonBlocking(UART0_BASE);
		if (receiveChar=='S' || receiveChar=='s')		//����S��s��ͣ		
		{
			TimerDisable(TIMER0_BASE,TIMER_A);
			LCDDrawingFlag_Pause=true;
		}

		if (receiveChar=='R' || receiveChar=='r')		//����R��r����
		{	
			TimerEnable(TIMER0_BASE,TIMER_A);
			LCDDrawingFlag_Running=true;
		}
	}	
}
