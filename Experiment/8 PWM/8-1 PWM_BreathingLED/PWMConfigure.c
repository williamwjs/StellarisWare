#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "PWMConfigure.h"

void PWMInitial(void)
{
/****************************Complete the code!!************************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);	//SysCtlʹ��PWMģ��
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);		//SysCtl������PWMʱ��Ԥ��ƵΪ1��Ƶ
	PWMGenConfigure(PWM_BASE,PWM_GEN_2,
					PWM_GEN_MODE_DOWN |
					PWM_GEN_MODE_NO_SYNC);	//����PWM������Ϊ�ݼ�����ģʽ���첽����
											//ע�⣺ʹ�õ�PWM�������ĺ��������PWM�������й�
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,BreathingLEDPeriod);			//����PWM������������ΪBreathingLEDPeriod
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,BreathingLEDPeriod/2);			//���ó�ʼPWM������
	PWMOutputState(PWM_BASE,PWM_OUT_5_BIT,true);			//ʹ��PWM���
	PWMGenEnable(PWM_BASE,PWM_GEN_2);				//ʹ��PWM������
/***********************************************************************************/
}
