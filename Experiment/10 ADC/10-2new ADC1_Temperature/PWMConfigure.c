#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "PWMConfigure.h"

void PWMInitial(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);					//使能PWM模块
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);							//预分频为1
	PWMGenConfigure(PWM_BASE,
					PWM_GEN_2,
					PWM_GEN_MODE_DOWN |
					PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,START_SOUND_PERIOD);		//启动音
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,START_SOUND_PERIOD/2);
	PWMOutputState(PWM_BASE,PWM_OUT_5_BIT,true);
	PWMGenEnable(PWM_BASE,PWM_GEN_2);
	SysCtlDelay(TheSysClock/15);
	PWMGenDisable(PWM_BASE,PWM_GEN_2);
}

void BuzzerBeep(unsigned long ulPeriod,unsigned long ulTime)
{
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,ulPeriod);		
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,ulPeriod/2);
	TimerLoadSet(TIMER1_BASE,TIMER_A,ulTime);	
	PWMGenEnable(PWM_BASE,PWM_GEN_2);
	TimerEnable(TIMER1_BASE,TIMER_A);
}
