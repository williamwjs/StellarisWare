#ifndef __LCDDISPLAY_H_
#define __LCDDISPLAY_H_

#include "grlib/grlib.h"

#define LCD_CLOCK_STATE_LINE	200
#define LCD_THUMBWHEEL_LINE		60
#define LCD_SETBIT_LINE			100

extern volatile unsigned char LCDDrawingFlag_Running;
extern volatile unsigned char LCDDrawingFlag_Pause;
extern volatile unsigned char LCDDrawingFlag_Thumbwheel;

extern void LCDSystemCheckInformationDisplay(unsigned char tSystemState);
extern tRectangle ssRect[320];
extern tContext sContext;
extern tRectangle sRect;

#endif
