#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "UARTISR.h"
#include <cstring>

char tempChar[10]={'\0', '\0', '\0', '\0', '\0','\0', '\0', '\0', '\0', '\0'};
int i=0;
int cmpFlag;

void UART0_ISR(void)
{
	//unsigned char receiveChar;
	unsigned long ulStatus;
	
	ulStatus=UARTIntStatus(UART0_BASE,true);
	UARTIntClear(UART0_BASE,ulStatus);
	
	if ((ulStatus &	UART_INT_RX)||(ulStatus & UART_INT_RT))
	{
		tempChar[i]=UARTCharGetNonBlocking(UART0_BASE);
		
		if(tempChar[i]== '\r')
		{
			tempChar[i]='\0';
			cmpFlag=strcmp(tempChar,"AT");
			if(!cmpFlag)
			{
				UARTStringPut(UART0_BASE,"OK\n\r");
			}
			else
			{
				cmpFlag=strcmp(tempChar,"AT+IPR?");
				if(!cmpFlag)					
				{
					UARTStringPut(UART0_BASE,"+IPR 19200\n\r");
				}
				else
				{
					UARTStringPut(UART0_BASE,"ERROR\n\r");					
				}
			}
			i=0;
		}
		else {i++;}		 
	}	
}
