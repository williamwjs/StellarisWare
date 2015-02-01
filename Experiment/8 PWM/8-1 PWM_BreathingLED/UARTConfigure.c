#include <stdio.h>
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

	UARTFIFOLevelSet(UART0_BASE, 
					 UART_FIFO_TX4_8,				//设置FIFO发射深度为4/8
					 UART_FIFO_RX1_8);				//设置FIFO接收深度为1/8
 	UARTIntEnable(UART0_BASE,UART_INT_RX |
				  			 UART_INT_RT);			//使能接收中断和接收超时中断
	IntEnable(INT_UART0);
	UARTEnable(UART0_BASE);							//使能UART0   
}

void UARTStringPut(unsigned long ulBase,const char *message)
{
	while(*message!='\0')
	{
		UARTCharPut(ulBase,*(message++));
	}
}

void UART1Initial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);	//使能UART1模块  
	UARTConfigSet(UART1_BASE,						//配置为UART1端口 
    			  9600,       						//波特率：9600 
    			  UART_CONFIG_WLEN_8 |				//数据位：8 
    			  UART_CONFIG_STOP_ONE |			//停止位：1 
    			  UART_CONFIG_PAR_NONE);   			//校验位：无 
	UARTEnable(UART1_BASE);							//使能UART1   
}

void UARTSystemCheckInformationTransmit(unsigned long ulBase,
										unsigned char tSystemState)
{
	char tempMessage[40];
	UARTStringPut(ulBase,"ARM Microcontroller Model:\tStellaris LM3S9B96\r\n");
	UARTStringPut(ulBase,"Manufacturer:\t\t\tTexas Instruments\r\n");
	UARTStringPut(ulBase,"Crystal Oscillator Frequencey:\t16000000 Hz\r\n");
	sprintf(tempMessage,"Main Clock Frequencey:\t\t%d Hz\r\n",SysCtlClockGet());
	UARTStringPut(ulBase,tempMessage);
	if (SysCtlLDOGet()<0x10)
		sprintf(tempMessage,"LDO Voltage:\t\t\t%d mV\r\n",(2500-SysCtlLDOGet()*50));
	else
		sprintf(tempMessage,"LDO Voltage:\t\t\t%d mV\r\n",(2500+(0x20-SysCtlLDOGet())*50));
	UARTStringPut(ulBase,tempMessage);
	UARTStringPut(ulBase,"Reset Cause:\t\t\t");
	if (SysCtlResetCauseGet() & SYSCTL_CAUSE_EXT)	UARTStringPut(ulBase,"EXT ");	//外部复位
	if (SysCtlResetCauseGet() & SYSCTL_CAUSE_POR)	UARTStringPut(ulBase,"POR ");	//上电复位
	if (SysCtlResetCauseGet() & SYSCTL_CAUSE_BOR)	UARTStringPut(ulBase,"BOR ");	//掉电复位
	if (SysCtlResetCauseGet() & SYSCTL_CAUSE_WDOG)	UARTStringPut(ulBase,"WDOG ");	//看门狗复位
	if (SysCtlResetCauseGet() & SYSCTL_CAUSE_SW)	UARTStringPut(ulBase,"SW ");	//软件复位
	if (SysCtlResetCauseGet() & SYSCTL_CAUSE_LDO)	UARTStringPut(ulBase,"LDO ");	//LDO原因复位
	if (!(SysCtlResetCauseGet() & 0x3f))			UARTStringPut(ulBase,"UNKNOWN");
	sprintf(tempMessage,"\r\nFlash Size:\t\t\t%d Bytes\r\n",SysCtlFlashSizeGet());
	UARTStringPut(ulBase,tempMessage);
	sprintf(tempMessage,"SRAM Size:\t\t\t%d Bytes\r\n",SysCtlSRAMSizeGet());
	UARTStringPut(ulBase,tempMessage);
	UARTStringPut(ulBase,"Initial Done!\r\n\r\n");
	if (tSystemState & 0x01)	UARTStringPut(ulBase,"I2C Pull-up Device Down\r\n");
	if (!tSystemState)			UARTStringPut(ulBase,"System All Green\r\n");
	UARTStringPut(ulBase,"Press the KEY to continue~\r\n");
}
