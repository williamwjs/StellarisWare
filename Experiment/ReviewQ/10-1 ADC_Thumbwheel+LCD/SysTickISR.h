#ifndef __SYSTICKISR_H_
#define __SYSTICKISR_H_

extern volatile unsigned char KeyNumber;			//0-None 1-Press 2-Left 3-Right 4-Up 5-Down
extern volatile unsigned char KeyNumberPresent;
extern volatile unsigned char KeyHoldFlag;

extern volatile unsigned char SystemActivatedFlag;

extern volatile unsigned char SetFlag;
extern volatile unsigned char SetBitFlag;	

extern volatile unsigned char CounterSecond;
extern volatile unsigned char CounterMinute;

extern volatile unsigned char SetSecond;
extern volatile unsigned char SetMinute;

#endif
