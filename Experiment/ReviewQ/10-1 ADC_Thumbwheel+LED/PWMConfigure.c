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
					PWM_GEN_MODE_NO_SYNC);			//����PWM������Ϊ�ݼ�����ģʽ���첽����
								                   //ע�⣺ʹ�õ�PWM�������ĺ��������PWM�������й�
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,START_SOUND_PERIOD);	      //����PWM������������ΪSTART_SOUND_PERIOD
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,START_SOUND_PERIOD/2);	  //���ó�ʼռ�ձ�Ϊ50%
	PWMOutputState(PWM_BASE,PWM_OUT_5_BIT,true);			      //ʹ��PWM���
	PWMGenEnable(PWM_BASE,PWM_GEN_2);				              //ʹ��PWM������
	SysCtlDelay(TheSysClock/15);				                  //��ʱ200ms
	PWMGenDisable(PWM_BASE,PWM_GEN_2);			                  //�ر�PWM�����PWM������
/***********************************************************************************/
}

void BuzzerBeep(unsigned long ulPeriod,unsigned long ulTime)
{
/****************************Complete the code!!************************************/
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,ulPeriod);			//����PWM������������Ϊ�������ulPeriod
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,ulPeriod/2);			//����ռ�ձ�Ϊ50%
	TimerLoadSet(TIMER1_BASE,TIMER_A,ulTime);				//����TIMER1A�Ķ�ʱ��ΪulTime(��TIMER���ڶ�ʱ�رշ�����)
	PWMGenEnable(PWM_BASE,PWM_GEN_2);				//ʹ��PWM��������PWM���
	TimerEnable(TIMER1_BASE,TIMER_A);				//ʹ��TIMER1A
/***********************************************************************************/
}
