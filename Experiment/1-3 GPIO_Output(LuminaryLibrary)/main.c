#include "inc/hw_memmap.h"		//基址宏定义			
#include "inc/hw_types.h"		//数据类型宏定义，寄存器访问函数	
#include "driverlib/debug.h"	//调试用	
#include "driverlib/gpio.h" 	//通用IO口宏定义	
#include "driverlib/sysctl.h"	//系统控制宏定义			

/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	低电平有效
*/

int main(void)						
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//使能端口（无需空等待语句）	
	GPIODirModeSet(GPIO_PORTF_BASE,						//设置为输出
				   GPIO_PIN_2 | 
				   GPIO_PIN_3,
				   GPIO_DIR_MODE_OUT);
	GPIOPadConfigSet(GPIO_PORTF_BASE,					//设置为8mA，带转换速率控制的推挽输出
					 GPIO_PIN_2 | 
					 GPIO_PIN_3,
					 GPIO_STRENGTH_8MA_SC,
					 GPIO_PIN_TYPE_STD);
	/*简略设置：
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
						  GPIO_PIN_2 |
						  GPIO_PIN_3);	//设置为2mA推挽输出
	*/						   
	GPIOPinWrite(GPIO_PORTF_BASE,						//点亮LED1
				 GPIO_PIN_2,
				 ~GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE,						//点亮LED0
				 GPIO_PIN_3,
				 ~GPIO_PIN_3);
	while(1);
}
