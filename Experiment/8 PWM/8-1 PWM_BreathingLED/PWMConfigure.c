#include "HardwareLibrary.h"
#include "LuminaryDriverLibrary.h"

#include "SysCtlConfigure.h"
#include "PWMConfigure.h"

void PWMInitial(void)
{
/****************************Complete the code!!************************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);	//SysCtl使能PWM模块
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);		//SysCtl中设置PWM时钟预分频为1分频
	PWMGenConfigure(PWM_BASE,PWM_GEN_2,
					PWM_GEN_MODE_DOWN |
					PWM_GEN_MODE_NO_SYNC);	//配置PWM发生器为递减技术模式，异步更新
											//注意：使用的PWM发生器的号码与输出PWM的引脚有关
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,BreathingLEDPeriod);			//设置PWM发生器的周期为BreathingLEDPeriod
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,BreathingLEDPeriod/2);			//设置初始PWM输出宽度
	PWMOutputState(PWM_BASE,PWM_OUT_5_BIT,true);			//使能PWM输出
	PWMGenEnable(PWM_BASE,PWM_GEN_2);				//使能PWM发生器
/***********************************************************************************/
}
