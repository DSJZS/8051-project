#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit DA = P2^1;

unsigned char Counter,Compare;
unsigned char i;

void main()
{
	Timer0_Init();

	while(1)
	{
		for(i=0;i<100;++i)
		{
			Compare = i;
			Delay(10);
		}
		for(i=100;i>0;--i)
		{
			Compare = i;
			Delay(10);
		}
	}
}

//	计时器0中断函数模板
void Timer0_Routine(void) interrupt 1
{
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	++Counter;
	if(Counter >= 100)
		Counter = 0;
	if(Counter < Compare)
		DA = 1;
	else
		DA = 0;
}