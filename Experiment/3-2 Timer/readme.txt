学习目的：
		了解Timer模块的功能；
		学会设置Timer计数器；
		从两个计数器并行工作中理解计数器的并行性。

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
		按住五向键中的Press，则将黄色网络灯(LED0)和绿色网络灯(LED1)将分别闪烁。
		黄色网络灯（LED0）每次点亮时长为0.5S，闪烁周期为1S;
		绿色网络灯（LED1）每次点亮时长为0.17秒,闪烁周期为0.33S；
		放开Press立即停止。