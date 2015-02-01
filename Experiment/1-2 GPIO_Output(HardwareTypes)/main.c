#include "inc/hw_types.h"				//数据类型宏定义，寄存器访问函数
#include "inc/hw_memmap.h"				//基址宏定义
#include "inc/hw_sysctl.h"				//系统控制宏定义
#include "inc/hw_gpio.h"				//通用IO口宏定义
/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	低电平有效
*/

int main(void)							
{   
/*
GPIO	数字输出配置：
AFSEL	DIR		ODR		DEN		PUR		PDR		DR2R	DR4R	DR8R	SLR
0		1		0		1		?		?		?		?		?		?	
X代表忽略，？根据具体情况设定
*/                           		
	HWREG(SYSCTL_RCGC2)=0x00000020;		//使能PORTF，需等待几个时钟周期
	__nop();							//asm空语句
	__nop();

	HWREG(GPIO_PORTF_BASE+GPIO_O_DEN)=0x0000000c;		//使能PORTF的数字模块
	HWREG(GPIO_PORTF_BASE+GPIO_O_DIR)=0x000c;			//设为输出模式
	HWREGH(GPIO_PORTF_BASE+GPIO_O_AFSEL)=0x0000;		//关闭备用功能
	HWREGH(GPIO_PORTF_BASE+GPIO_O_DR8R)=0x000c;			//设置输出电流为8-mA（2-mA和4-mA的寄存器自动清零）
	HWREGB(GPIO_PORTF_BASE+GPIO_O_ODR)=0x00;			//设为推挽输出(可以不设置，默认）
	HWREGB(GPIO_PORTF_BASE+GPIO_O_SLR)=0x0c;			//打开斜率控制（跳变速度控制）
	HWREGB(GPIO_PORTF_BASE+GPIO_O_DATA+0x3fc)=0x04;		//打开LED0，关闭LED1
	while(1);
}
