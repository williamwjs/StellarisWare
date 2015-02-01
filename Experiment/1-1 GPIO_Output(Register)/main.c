/*
LED0(Yellow)-->PF3,	LED1(Green)-->PF2	低电平有效
*/

//寄存器地址定义
#define RCGC2		(*((volatile unsigned long *)(0x400FE108)))	//各模块时钟门控控制寄存器 *注意不是DATASHEET上的0x000
#define GPIOFDATA	(*((volatile unsigned long *)(0x400253fc)))	//PortF 数据寄存器
#define GPIOFDIR	(*((volatile unsigned long *)(0x40025400)))	//PortF 方向寄存器
#define GPIOFAFSEL	(*((volatile unsigned long *)(0x40025420)))	//PortF 备用功能选择寄存器
#define GPIOFDR2R	(*((volatile unsigned long *)(0x40025500)))	//PortF 2-mA驱动寄存器
#define GPIOFDR4R	(*((volatile unsigned long *)(0x40025504)))	//PortF 4-mA驱动寄存器
#define GPIOFDR8R	(*((volatile unsigned long *)(0x40025508)))	//PortF 8-mA驱动寄存器
#define GPIOFODR	(*((volatile unsigned long *)(0x4002550c)))	//PortF 开漏选择寄存器
#define GPIOFDEN	(*((volatile unsigned long *)(0x4002551c)))	//PortF 数字使能寄存器
#define GPIOFSLR	(*((volatile unsigned long *)(0x40025518)))	//PortF 斜率寄存器

int main(void)						//主函数
{   
/*
GPIO	数字输出配置：
AFSEL	DIR		ODR		DEN		PUR		PDR		DR2R	DR4R	DR8R	SLR
0		1		0		1		?		?		?		?		?		?	
X代表忽略，？根据具体情况设定
*/                           		
    RCGC2=0x00000020;		//使能PORTF，需等待几个时钟周期
	__nop();				//asm空语句
	__nop();

	GPIOFDEN=0x0000000c;	//使能PORTF的数字模块
	GPIOFDIR=0x0000000c;	//设为输出模式
	GPIOFAFSEL=0x00000000;	//关闭备用功能
	GPIOFDR8R=0x0000000c;	//设置输出电流为8-mA（2-mA和4-mA的寄存器自动清零）
	GPIOFODR=0x00000000;	//设为推挽输出(可以不设置，默认）
	GPIOFSLR=0x0000000c;	//打开斜率控制（跳变速度控制）
	GPIOFDATA=0x00000004;	//打开LED0，关闭LED1
	while(1);
}
