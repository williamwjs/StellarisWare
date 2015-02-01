#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "GPIODriverConfigure.h"
#include "SysCtlConfigure.h"
#include "SysTickConfigure.h"
#include "TimerConfigure.h"
#include "WatchDogConfigure.h"

unsigned char BlinkFlag=true; 
 	
int main(void)											//������
{
	//��ʼ��
	ClockInitial();
	GPIOInitial();
	SysTickInitial();
	TimerInitial();								

	LEDOn(LED_ALL);
	while (!(KeyPress(KEY_LEFT) |
			 KeyPress(KEY_RIGHT) |
			 KeyPress(KEY_UP) |
			 KeyPress(KEY_DOWN)));
	LEDOff(LED_ALL);	

	IntMasterEnable();									//��Χ�жϿ���������SysTick��������ж϶�Ҫ������
	SysTickEnable();									//SysTick��ʼ����
	TimerEnable(TIMER0_BASE,TIMER_A);					//TIMER0��ʼ����
	WatchDogInitial();									//�������Ź�ģ��

	while(1);
}
