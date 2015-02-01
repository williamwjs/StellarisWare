#ifndef __LCDDISPLAY_H_
#define __LCDDISPLAY_H_


#define LCD_CLOCK_STATE_LINE	200
#define LCD_THUMBWHEEL_LINE		60
#define LCD_SETBIT_LINE			100

extern volatile unsigned char LCDDrawingFlag_Running;
extern volatile unsigned char LCDDrawingFlag_Pause;
extern volatile unsigned char LCDDrawingFlag_Thumbwheel;

extern void LCDSystemCheckInformationDisplay(unsigned char tSystemState);

#endif
