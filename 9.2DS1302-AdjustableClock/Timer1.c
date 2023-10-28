#include "Timer1.h"

void Timer1_Init(void)
{
	TMOD &= 0x0F;
	TMOD |= 0x10;
	TL1 = 0x66;				//设置定时初始值
	TH1 = 0xFC;				//设置定时初始值
	TF1 = 0;
	TR1 = 1;
	EA = 1;
	ET1 = 1;
	PT1 = 1;
}
