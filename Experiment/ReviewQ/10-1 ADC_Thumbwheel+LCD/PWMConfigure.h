#ifndef	__PWMCONFIGURE_H_
#define __PWMCONFIGURE_H_

#define START_SOUND_PERIOD			TheSysClock/1000	
#define ALARM_SOUND_PERIOD			TheSysClock/2000
#define SET_SOUND_PERIOD			TheSysClock/800

extern void PWMInitial(void);
extern void BuzzerBeep(unsigned long ulPeriod,
					   unsigned long ulTime);

#endif
