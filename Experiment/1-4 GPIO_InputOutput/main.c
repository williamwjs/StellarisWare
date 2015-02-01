#include "inc/hw_memmap.h"		//基址宏定义			
#include "inc/hw_types.h"		//数据类型宏定义，寄存器访问函数	
#include "driverlib/debug.h"	//调试用	
#include "driverlib/gpio.h" 	//通用IO口宏定义	
#include "driverlib/sysctl.h"	//系统控制宏定义

/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	低电平有效

五向键
SW_1	JP43	PB6		Right
SW_2	JP41	PE5		Press
SW_3	JP42	PE4		Up
SW_4	JP44	PF1		Down
SW_5	JP45	PB4		Left
低电平触发
*/

int main(void)					
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);		//使能端口B
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);		//使能端口E
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);		//使能端口F

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,				//PF2,PF3设置为2mA推挽输出
						  GPIO_PIN_2 |
						  GPIO_PIN_3);								   
	GPIOPinWrite(GPIO_PORTF_BASE,						//LED0,LED0齐灭
				 GPIO_PIN_2,
				 GPIO_PIN_2);
	GPIOPinWrite(GPIO_PORTF_BASE,
				 GPIO_PIN_3,
				 GPIO_PIN_3);

	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE,			 	//设置PB6,PE5,PE4,PF1,PB4为输入
						 GPIO_PIN_4 | 
						 GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,
						 GPIO_PIN_4 | 
						 GPIO_PIN_5);	
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,
						 GPIO_PIN_1);
		
	while(1)
	{
		if (((GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6)>>2) &
			  GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_4))==0)				//左或右
		{
			GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2);		//LED1灭
			GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,~GPIO_PIN_3);		//LED0亮
		}
		else
		{
			if (((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_4)>>3) &
			 	  GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_1))== 0)			//上或下
			{
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,~GPIO_PIN_2);	//LED1亮
				GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,GPIO_PIN_3);	//LED0灭
			}
			else
			{
				if ((GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_5)>>5)==0)	//按下
				 
					GPIOPinWrite(GPIO_PORTF_BASE,
								 GPIO_PIN_2 |
								 GPIO_PIN_3,
								 ~GPIO_PIN_2 &
								 ~GPIO_PIN_3);							//LED0及LED1亮
				
				else	
					GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2 |
								 GPIO_PIN_3,
								 GPIO_PIN_2 |
								 GPIO_PIN_3);							//关闭LED0和LED1
			}
		} 	 
	}							   
}
