#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"	 

unsigned long TheSysClock = 16000000UL;

//  ϵͳʱ�ӳ�ʼ��
void ClockInitial(void)
{
	
	/*
	SysCtlLDOSet(SYSCTL_LDO_2_50V);
	SysCtlClockSet(SYSCTL_USE_OSC |
				   SYSCTL_OSC_INT4 |
				   SYSCTL_SYSDIV_1);
	*/
 	/*
	SysCtlLDOSet(SYSCTL_LDO_2_50V);			//  ����LDO�����ѹ
	SysCtlClockSet(SYSCTL_USE_OSC |			//  ϵͳʱ������
                   SYSCTL_OSC_MAIN |		//  ����������
                   SYSCTL_XTAL_16MHZ |		//  ���16MHz����
                   SYSCTL_SYSDIV_1);		//  ����Ƶ
	*/
	
	SysCtlLDOSet(SYSCTL_LDO_2_75V);			//  ����PLLǰ�뽫LDO��Ϊ2.75V
	SysCtlClockSet(SYSCTL_USE_PLL |			//  ϵͳʱ�����ã�����PLL
                   SYSCTL_OSC_MAIN |		//  ������
                   SYSCTL_XTAL_16MHZ |		//  ���16MHz����
                   SYSCTL_SYSDIV_4);		//  ��Ƶ���Ϊ50MHz

	TheSysClock = SysCtlClockGet();			//  ��ȡ��ǰ��ϵͳʱ��Ƶ��
}
