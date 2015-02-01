#ifndef __LCDDISPLAY_H_
#define __LCDDISPLAY_H_

extern volatile unsigned char LCDDrawingFlag_Running;
extern volatile unsigned char LCDDrawingFlag_Pause;

extern void LCDSystemCheckInformationDisplay(unsigned char tSystemState);

#endif
