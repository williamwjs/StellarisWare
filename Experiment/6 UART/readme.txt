学习目的：
		了解UART总线的基本协议、功能与用途；
		学会使用UART总线与上位机作交互；
		理解char型数据与ASCII码的关系，会用转义字符。

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
		初始状态下黄色网络灯（LED0）与绿色网络灯（LED1）齐亮。
		初始化完成后UART向上位机发送信息：											 ·	
			Initial Done！
			Press the KEY to continue~
		此时按下Press键，系统启动。
		启动后系统会处于4种状态：
			状态1：为默认状态，或按下DOWN后启动。此时仅将上位机发送的信息原样返回。	
					该状态下LED0与LED1齐灭。
			状态2：按下LEFT后启动，此时除了‘a’～‘z’外的所有信息原样返回，‘a’～‘z’转换为‘A’~‘Z’后返回。
					该状态下LED1亮。
			状态3：按下RIGHT后启动，此时除了‘A’～‘Z’外的所有信息原样返回，‘A’～‘Z’转换为‘a’~‘z’后返回。
					该状态下LED0亮。
			状态4：按下UP后启动，此时将英文字母中的小写字符转换为大写字符，将大写字符转换为小写字符并返回，
					其他字符原样返回。
					该状态下LED0与LED1齐亮。
		注意：若有字符输入，系统返回时每隔最多1S会自动换行

		