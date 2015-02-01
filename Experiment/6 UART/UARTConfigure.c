#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "UARTConfigure.h"

void UART0Initial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);	//使能UART0模块  
	UARTConfigSet(UART0_BASE,						//配置为UART0端口 
    			  115200,       					//波特率：115200 
    			  UART_CONFIG_WLEN_8 |				//数据位：8 
    			  UART_CONFIG_STOP_ONE |			//停止位：1 
    			  UART_CONFIG_PAR_NONE);   			//校验位：无 
	UARTEnable(UART0_BASE);							//使能UART0   
}

void UARTStringPut(unsigned long ulBase,const char *cMessage)
{
	while(*cMessage!='\0')
	{
		UARTCharPut(ulBase,*(cMessage++));
	}
}
