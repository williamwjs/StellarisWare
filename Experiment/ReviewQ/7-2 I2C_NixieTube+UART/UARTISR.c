#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "UARTISR.h"
#include "NixieTubeConfigure.h"
#include <cstring>

char tempChar[10]={'\0', '\0', '\0', '\0', '\0','\0', '\0', '\0', '\0', '\0'};
int i=0,j=0;
int tempInt[4],result;
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
			for(j=0;j<4;j++)
			{
				tempInt[j]=tempChar[j]-'0';
			}
			result=tempInt[0]*1000+tempInt[1]*100+tempInt[2]*10+tempInt[3];
			//result=(int)(tempChar);
			sprintf(NixieTube,"%04d:",result);
			i=0;
		}
		else {i++;}		 
	}	
}
