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
					PWM_GEN_MODE_NO_SYNC);			//配置PWM发生器为递减技术模式，异步更新
								                   //注意：使用的PWM发生器的号码与输出PWM的引脚有关
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,START_SOUND_PERIOD);	      //设置PWM发生器的周期为START_SOUND_PERIOD
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,START_SOUND_PERIOD/2);	  //设置初始占空比为50%
	PWMOutputState(PWM_BASE,PWM_OUT_5_BIT,true);			      //使能PWM输出
	PWMGenEnable(PWM_BASE,PWM_GEN_2);				              //使能PWM发生器
	SysCtlDelay(TheSysClock/15);				                  //延时200ms
	PWMGenDisable(PWM_BASE,PWM_GEN_2);			                  //关闭PWM输出或PWM发生器
/***********************************************************************************/
}

void BuzzerBeep(unsigned long ulPeriod,unsigned long ulTime)
{
/****************************Complete the code!!************************************/
	PWMGenPeriodSet(PWM_BASE,PWM_GEN_2,ulPeriod);			//设置PWM发生器的周期为输入变量ulPeriod
	PWMPulseWidthSet(PWM_BASE,PWM_OUT_5,ulPeriod/2);			//设置占空比为50%
	TimerLoadSet(TIMER1_BASE,TIMER_A,ulTime);				//设置TIMER1A的定时数为ulTime(该TIMER用于定时关闭蜂鸣器)
	PWMGenEnable(PWM_BASE,PWM_GEN_2);				//使能PWM发生器和PWM输出
	TimerEnable(TIMER1_BASE,TIMER_A);				//使能TIMER1A
/***********************************************************************************/
}
