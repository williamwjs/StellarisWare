#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"	 

unsigned long TheSysClock = 16000000UL;

//  ϵͳʱ�ӳ�ʼ��
void ClockInitial(void)
{
	SysCtlLDOSet(SYSCTL_LDO_2_50V);			//  ����LDO�����ѹ
	SysCtlClockSet(SYSCTL_USE_OSC |			//  ϵͳʱ������
                   SYSCTL_OSC_MAIN |		//  ����������
                   SYSCTL_XTAL_16MHZ |		//  ���16MHz����
                   SYSCTL_SYSDIV_1);		//  ����Ƶ

	TheSysClock = SysCtlClockGet();			//  ��ȡ��ǰ��ϵͳʱ��Ƶ��
}

