#ifndef __UARTCONFIGURE_H_
#define __UARTCONFIGURE_H_

extern void UART0Initial(void);
extern void UARTStringPut(unsigned long ulBase,const char *);

extern void UART1Initial(void);

extern void UARTSystemCheckInformationTransmit(unsigned long ulBase,unsigned char tSystemState);

#endif