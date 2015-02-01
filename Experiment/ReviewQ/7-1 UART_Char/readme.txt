学习目的：
		了解I2C总线的特点和功能；
		学会使用I2C自检程序；
		会使用I2C总线对PCA9557芯片进行操作；
		学会常用键盘防抖方法。---------------------SysTickISR

实验准备工作：
		连接			断开
		JP3		PF2		JP35		LED1
		JP2		PF3		JP39		LED0
		JP43	PB6		JP20,JP28	SW1-RIGHT
		JP41	PE5		JP24		SW2-PRESS
		JP42	PE4		JP25		SW3-UP
		JP44	PF1		JP30		SW4-DOWN
		JP45	PB4		JP48		SW5-LEFT
		打开SSCOM。

实验效果：
		系统初始化后黄色网络灯（LED0）与绿色网络灯（LED1）齐亮。
		此时按下五向键中的任一键，系统启动。
		此时按下五向键中的任一键，对应LED灯点亮。
		