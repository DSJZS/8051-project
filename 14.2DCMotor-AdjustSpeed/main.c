#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"
#include "Nixie.h"

sbit Motor = P1^0;

unsigned char Counter,Compare;
unsigned char KeyNum=0,Speed=0;

void main()
{
	Timer0_Init();

	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum == 1)
			{
				++Speed;
				if(Speed>3)
					Speed=0;
				if(Speed == 0){	Compare=0;}
				if(Speed == 1){	Compare=50;}
				if(Speed == 2){	Compare=75;}
				if(Speed == 3){	Compare=100;}
			}
		}

		Nixie(1,Speed);
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
		Motor = 1;
	else
		Motor = 0;
}