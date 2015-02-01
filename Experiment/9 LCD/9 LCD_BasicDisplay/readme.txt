学习目的：
		了解I2C总线的特点和功能；
		学会使用I2C自检程序；
		会使用I2C总线对PCA9557芯片进行操作；
		学会常用键盘防抖方法。

实验准备工作：
		连接			断开
		JP3		PF2		JP35		LED1
		JP43	PB6		JP20,JP28	SW1-RIGHT
		JP41	PE5		JP24		SW2-PRESS
		JP42	PE4		JP25		SW3-UP
		JP44	PF1		JP30		SW4-DOWN
		JP45	PB4		JP48		SW5-LEFT
		JP39	PF3		JP2			BUZZER
		JP38	PB7					LCD_RST\
		JP11			JP12		LCD_CS\(下拉)
		JP6		PD0		JP29,JP36	LCD_D0
		JP7		PD1		JP27,JP37	LCD_D1
		JP8		PD4		JP26		LCD_D4
		JP9		PD5		JP31		LCD_D5
						JP23		LCD_Backlight
		打开SSCOM。

实验效果：
		可设置目标时间的电子钟
		带状态显示屏
		