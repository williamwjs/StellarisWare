#include "NixieTubeConfigure.h"

#define NixieTubeCharNumber	43

char NixieTube[6]={0};
unsigned char volatile LEDSerial=0x01;

unsigned char volatile NixieTubeSlice=0;
unsigned char volatile NixieTubeSegment=0;
unsigned char volatile NixieTubeSelected1=0;
unsigned char volatile NixieTubeSelected2=0;

unsigned char volatile NixieTubeSpecialSignal1=0;
unsigned char volatile NixieTubeSpecialSignal2=0;

static const char NixieTubeCodeTable[NixieTubeCharNumber][2]=
{
	{0x14,0xff},	//'0'	
    {0x00,0x18},	//'1'
	{0x70,0x2c},	//'2'
	{0x70,0x26},	//'3'
	{0x60,0x32},	//'4'
	{0x70,0x16},	//'5'
	{0x70,0x1e},	//'6'
	{0x08,0x04},	//'7'
	{0x70,0xff},	//'8'
	{0x70,0xf7},	//'9'
	{0x60,0xff},	//'A'
	{0x5a,0x26},	//'B'
	{0x10,0x1c},	//'C'
	{0x1a,0x26},	//'D'
	{0x70,0x1c},	//'E'
	{0x60,0x1c},	//'F'
	{0x50,0x1e},	//'G'
	{0x60,0xfb},	//'H'
	{0x1a,0x04},	//'I'
	{0x10,0x26},	//'J'	 
	{0x20,0x18},	//'K'
	{0x10,0x18},	//'L'
	{0x80,0xfb},	//'M'
	{0x80,0xfb},	//'N'
	{0x10,0xff},	//'O'
	{0x60,0xfd},	//'P'
	{0x10,0xff},	//'Q'
	{0x60,0xfd},	//'R'
	{0xd0,0x06},	//'S'
	{0x0a,0x04},	//'T'
	{0x10,0xfb},	//'U'
	{0x04,0x18},	//'V'
	{0x04,0xfb},	//'W'
	{0x84,0x00},	//'X'
	{0x88,0x00},	//'Y'
	{0x14,0x04},	//'Z'
	{0x6a,0x00},	//'+'
	{0x60,0x00},	//'-'
	{0x8e,0x00},	//'*'
	{0x04,0x00},	//'/'
	{0x0a,0x00},	//'|'
	{0x80,0x00},	//'\'
	{0x00,0x00}		//None		
};

static const char NixieTubeSpecialCodeTable[4][43][2]=
{
	{
		{0x00,0x04},	//'0'	
		{0x00,0x00},	//'1'
		{0x00,0x00},	//'2'
		{0x00,0x00},	//'3'
		{0x00,0x00},	//'4'
		{0x00,0x00},	//'5'
		{0x00,0x00},	//'6'
		{0x00,0x04},	//'7'
		{0x00,0x00},	//'8'
		{0x00,0x00},	//'9'
		{0x00,0x00},	//'A'
		{0x00,0x00},	//'B'	    
		{0x00,0x00},	//'C'
		{0x00,0x00},	//'D'
		{0x00,0x00},	//'E'
		{0x00,0x00},	//'F'
		{0x00,0x00},	//'G'
		{0x00,0x00},	//'H'
		{0x00,0x00},	//'I'
		{0x00,0x00},	//'J'	 
		{0x00,0x0c},	//'K'
		{0x00,0x00},	//'L'
		{0x00,0x04},	//'M'
		{0x00,0x08},	//'N'
		{0x00,0x00},	//'O'
		{0x00,0x00},	//'P'
		{0x00,0x08},	//'Q'
		{0x00,0x08},	//'R'
		{0x00,0x00},	//'S'
		{0x00,0x00},	//'T'
		{0x00,0x00},	//'U'
		{0x00,0x04},	//'V'
		{0x00,0x08},	//'W'
		{0x00,0x0c},	//'X'
		{0x00,0x04},	//'Y'
		{0x00,0x04},	//'Z'
		{0x00,0x00},	//'+'
		{0x00,0x00},	//'-'
		{0x00,0x0c},	//'*'
		{0x00,0x04},	//'/'
		{0x00,0x00},	//'|'
		{0x00,0x08},	//'\'
		{0x00,0x00}		//None
	},
	{
		{0x00,0x20},	//'0'	 
		{0x00,0x00},	//'1'
		{0x00,0x00},	//'2'
		{0x00,0x00},	//'3'
		{0x00,0x00},	//'4'
		{0x00,0x00},	//'5'
		{0x00,0x00},	//'6'
		{0x00,0x20},	//'7'
		{0x00,0x00},	//'8'
		{0x00,0x00},	//'9'
		{0x00,0x00},	//'A'
		{0x00,0x00},	//'B'
		{0x00,0x00},	//'C'
		{0x00,0x00},	//'D'
		{0x00,0x00},	//'E'
		{0x00,0x00},	//'F'
		{0x00,0x00},	//'G'
		{0x00,0x00},	//'H'
		{0x00,0x00},	//'I'
		{0x00,0x00},	//'J'	
		{0x00,0x30},	//'K'
		{0x00,0x00},	//'L'
		{0x00,0x20},	//'M'
		{0x00,0x10},	//'N'
		{0x00,0x00},	//'O'
		{0x00,0x00},	//'P'
		{0x00,0x10},	//'Q'
		{0x00,0x10},	//'R'
		{0x00,0x00},	//'S'
		{0x00,0x00},	//'T'
		{0x00,0x00},	//'U'
		{0x00,0x20},	//'V'
		{0x00,0x10},	//'W'
		{0x00,0x30},	//'X'
		{0x00,0x20},	//'Y'
		{0x00,0x20},	//'Z'
		{0x00,0x00},	//'+'
		{0x00,0x00},	//'-'
		{0x00,0x30},	//'*'
		{0x00,0x20},	//'/'
		{0x00,0x00},	//'|'
		{0x00,0x10},	//'\'
		{0x00,0x00}		//None
	},
	{
		{0x00,0x02},	//'0'	 
		{0x00,0x00},	//'1'
		{0x00,0x00},	//'2'
		{0x00,0x00},	//'3'
		{0x00,0x00},	//'4'
		{0x00,0x00},	//'5'
		{0x00,0x00},	//'6'
		{0x00,0x02},	//'7'
		{0x00,0x00},	//'8'
		{0x00,0x00},	//'9'
		{0x00,0x00},	//'A'
		{0x00,0x00},	//'B'
		{0x00,0x00},	//'C'
		{0x00,0x00},	//'D'
		{0x00,0x00},	//'E'
		{0x00,0x00},	//'F'
		{0x00,0x00},	//'G'
		{0x00,0x00},	//'H'
		{0x00,0x00},	//'I'
		{0x00,0x00},	//'J'	
		{0x20,0x02},	//'K'
		{0x00,0x00},	//'L'
		{0x00,0x02},	//'M'
		{0x20,0x00},	//'N'
		{0x00,0x00},	//'O'
		{0x00,0x00},	//'P'
		{0x20,0x00},	//'Q'
		{0x20,0x00},	//'R'
		{0x00,0x00},	//'S'
		{0x00,0x00},	//'T'
		{0x00,0x00},	//'U'
		{0x00,0x02},	//'V'
		{0x20,0x00},	//'W'
		{0x20,0x02},	//'X'
		{0x00,0x02},	//'Y'
		{0x00,0x02},	//'Z'
		{0x00,0x00},	//'+'
		{0x00,0x00},	//'-'
		{0x20,0x02},	//'*'
		{0x00,0x02},	//'/'
		{0x00,0x00},	//'|'
		{0x20,0x00},	//'\'
		{0x00,0x00}		//None
	},
	{
		{0x10,0x00},	//'0'	
		{0x00,0x00},	//'1'
		{0x00,0x00},	//'2'
		{0x00,0x00},	//'3'
		{0x00,0x00},	//'4'
		{0x00,0x00},	//'5'
		{0x00,0x00},	//'6'
		{0x10,0x00},	//'7'
		{0x00,0x00},	//'8'
		{0x00,0x00},	//'9'
		{0x00,0x00},	//'A'
		{0x00,0x00},	//'B'
		{0x00,0x00},	//'C'
		{0x00,0x00},	//'D'
		{0x00,0x00},	//'E'
		{0x00,0x00},	//'F'
		{0x00,0x00},	//'G'
		{0x00,0x00},	//'H'
		{0x00,0x00},	//'I'
		{0x00,0x00},	//'J'	 
		{0x50,0x00},	//'K'
		{0x00,0x00},	//'L'
		{0x10,0x00},	//'M'
		{0x40,0x00},	//'N'
		{0x00,0x00},	//'O'
		{0x00,0x00},	//'P'
		{0x40,0x00},	//'Q'
		{0x40,0x00},	//'R'
		{0x00,0x00},	//'S'
		{0x00,0x00},	//'T'
		{0x00,0x00},	//'U'
		{0x10,0x00},	//'V'
		{0x40,0x00},	//'W'
		{0x50,0x00},	//'X'
		{0x10,0x00},	//'Y'
		{0x10,0x00},	//'Z'
		{0x00,0x00},	//'+'
		{0x00,0x00},	//'-'
		{0x50,0x00},	//'*'
		{0x10,0x00},	//'/'
		{0x00,0x00},	//'|'
		{0x40,0x00},	//'\'
		{0x00,0x00}		//None
	}
};

void NixieTubeCoding(void)
{
	unsigned char NixieTubePointer=0;	//查表指示符

/****************************Complete the code!!************************************/
	switch (NixieTubeSlice)
	{
		case 0:		NixieTubeSegment=~0x20;break;	//选择左数第1根米字管
		case 1:		NixieTubeSegment=~0x02;break;	//选择左数第2根米字管
		case 2:		NixieTubeSegment=~0x04;break;	//选择左数第3根米字管
		case 3:		NixieTubeSegment=~0x08;break;	//选择左数第4根米字管
		case 4:		NixieTubeSegment=~0x10;break;	//选择第5根特殊米字管
		default:	NixieTubeSegment=~0x20;break;						  
	}
/**********************************************************************************/
	if (NixieTubeSlice<4)
	{
		//查表转码
		if (NixieTube[NixieTubeSlice]==' ' ||
			NixieTube[NixieTubeSlice]==0)
				NixieTubePointer=42;
		if (NixieTube[NixieTubeSlice] >= '0' && NixieTube[NixieTubeSlice] <= '9')	
			NixieTubePointer=NixieTube[NixieTubeSlice]-48;
		else
		{
			if (NixieTube[NixieTubeSlice] >= 'A' && NixieTube[NixieTubeSlice] <= 'Z')	
				NixieTubePointer=NixieTube[NixieTubeSlice]-55;
			else
			{
				switch (NixieTube[NixieTubeSlice])
				{
					case '+':	NixieTubePointer=36;break;
					case '-':	NixieTubePointer=37;break;
					case '*':	NixieTubePointer=38;break;
					case '/':	NixieTubePointer=39;break;
					case '|':	NixieTubePointer=40;break;
					case '\\':	NixieTubePointer=41;break;
					default:	break;
				}	
			}
		}
		//保存待DIG5时用
		NixieTubeSpecialSignal1 +=
			NixieTubeSpecialCodeTable[NixieTubeSlice][NixieTubePointer][0];
		NixieTubeSpecialSignal2 +=
			NixieTubeSpecialCodeTable[NixieTubeSlice][NixieTubePointer][1];
		NixieTubeSelected1=NixieTubeCodeTable[NixieTubePointer][0];
		NixieTubeSelected2=NixieTubeCodeTable[NixieTubePointer][1];
	}
	else
	{
		switch (NixieTube[4])
		{
			case ' ':	NixieTubeSelected1=NixieTubeSpecialSignal1;break;
			case '`':	NixieTubeSelected1=NixieTubeSpecialSignal1+0x80;break;
			case '.':	NixieTubeSelected1=NixieTubeSpecialSignal1+0x02;break;
			case ':':	NixieTubeSelected1=NixieTubeSpecialSignal1+0x82;break;
			default:	NixieTubeSelected1=NixieTubeSpecialSignal1;break;
		}		
		NixieTubeSelected2=NixieTubeSpecialSignal2;
		NixieTubeSpecialSignal1=0;
		NixieTubeSpecialSignal2=0;
	}
	NixieTubeSlice++;
	if (NixieTubeSlice>4)	NixieTubeSlice=0;
}

