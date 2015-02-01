#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "UARTConfigure.h"

void UART0Initial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);	//ʹ��UART0ģ��  
	UARTConfigSet(UART0_BASE,						//����ΪUART0�˿� 
    			  115200,       					//�����ʣ�115200 
    			  UART_CONFIG_WLEN_8 |				//����λ��8 
    			  UART_CONFIG_STOP_ONE |			//ֹͣλ��1 
    			  UART_CONFIG_PAR_NONE);   			//У��λ���� 
	UARTEnable(UART0_BASE);							//ʹ��UART0   
}

void UARTStringPut(unsigned long ulBase,const char *cMessage)
{
	while(*cMessage!='\0')
	{
		UARTCharPut(ulBase,*(cMessage++));
	}
}
