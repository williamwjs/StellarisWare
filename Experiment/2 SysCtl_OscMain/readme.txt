学习目的：
		了解SysCtl模块的功能；
		学会根据具体实验板设置时钟频率；
		学会使用SysCtl库函数中的延时函数；
		学会自制延时函数；
		学会将必须的初始函数或常用函数封装。

实验准备工作：
		连接			断开
		JP3		PF2		JP35		LED1
		JP2		PF3		JP39		LED0
		JP43	PB6		JP20,JP28	SW1-RIGHT
		JP41	PE5		JP24		SW2-PRESS
		JP42	PE4		JP25		SW3-UP
		JP44	PF1		JP30		SW4-DOWN
		JP45	PB4		JP48		SW5-LEFT

实验效果：
		按住五向键中的Press，则将黄色网络灯(LED0)和绿色网络灯(LED1)将轮流点亮，每次点亮时长为0.5秒;
		放开Press在一个闪烁周期结束后将停止闪烁。