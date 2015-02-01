#ifndef __LCDCONFIGURE_H_		//LCD Module
#define __LCDCONFIGURE_H_

#ifdef LCD_KITRONIX320X240X16_SSD2119
	#define LANDSCAPE
	
	#define LCD_CONTROL_NRESET    0x04
	#define LCD_CONTROL_YN        0x02
	#define LCD_CONTROL_XN        0x01
		
	extern const tDisplay g_sKitronix320x240x16_SSD2119;
	extern void LCDInitial(void);
#endif

#endif
