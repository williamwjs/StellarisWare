#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"

unsigned char ShiningEnable=true;	//hw_types�ж��壬����Сд
 	
int main(void)						
{
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();	
	IntMasterEnable();									//��Χ�жϿ���������SysTick��������ж϶�Ҫ������

	SysTickEnable();									//SysTick��ʼ����
	TimerEnable(TIMER0_BASE,TIMER_A);					//TIMER0��ʼ����

	while(1);
}
