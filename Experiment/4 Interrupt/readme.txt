学习目的：
		了解中断的概念；
		学会设置中断向量表；
		学会中断函数的表达；
		学会GPIO,TIMER,SYSTICK模块的中断设置。

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
		按下五向键中除Press外的另外4个键，则将黄色网络灯(LED0)和绿色网络灯(LED1)将开始闪烁。
		黄色网络灯（LED0）每次点亮时长为1S，闪烁周期为2S；
		绿色网络灯（LED1）每次点亮时长为0.33秒，闪烁周期为0.67S；
		若按下五向键中的Press键则停止闪烁。