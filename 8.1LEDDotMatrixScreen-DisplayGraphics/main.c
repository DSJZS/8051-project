#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"
#include "Timer0.h"

unsigned char code Animation[]={
	0xFF,0x08,0x08,0x08,0xFF,0x00,0x0E,0x15,
	0x15,0x15,0x08,0x00,0x7E,0x01,0x02,0x00,
	0x7E,0x01,0x02,0x00,0x0E,0x11,0x11,0x0E,
	0x00,0x7D,0x00,0x7D,0x00,0x7D,0x00,0x00
};

unsigned char Offset=0;

void main()
{
	unsigned char i=0;
	MatrixLED_Init();
	Timer0_Init();
	while(1)
	{
		for(i=0;i<8;++i)
		{
			MatrixLED_ShowColum(i,Animation[ (i+Offset)%32 ]);
		}	
	}
}

void Timer0_Routine(void)	interrupt 1
{
	static unsigned int T0Count;
	
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	++T0Count;
	
	if(T0Count % 100 == 0)
	{
		T0Count = 0;
		++Offset;
		if(Offset>32)
		{
			Offset=0;
		}
	}
}