学习目的：
		了解GPIO的功能与作用，学会对端口的读与写操作；
		了解五向键的原理和使用。

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
		按住五向键中的Left或Right，则点亮黄色网络灯(LED0)；
		按住五向键中的Up或Down，则点亮绿色网络灯(LED1);
		按住五向键中的Press，则将黄色网络灯(LED0)和绿色网络灯(LED1)都点亮。