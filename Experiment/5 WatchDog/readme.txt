学习目的：
		了解看门狗的原理与作用；
		学会看门狗的初始化与喂狗。

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
		初始状态下黄色网络灯（LED0）与绿色网络灯（LED1）齐亮。
		此时按下Up，Down，Left与Right中的任一一键，黄色网络灯(LED0)将以警报灯的方式闪烁，具体闪烁循环如下：
			亮0.1S，暗0.1S，亮0.1S，暗0.1S，亮0.1S，暗0.5S。
		周期为1S。
		独立地，按下Press将点亮绿色网络灯（LED1）0.1S，并执行喂狗操作。看门狗周期设定为2S。
		
		因此，若在黄灯闪烁4个周期后，仍未喂狗，则系统会重启，回到初始状态