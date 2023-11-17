#include "Motor.h"
#include "Timer1.h"
#include <REGX52.H>


sbit Motor = P1^0;

unsigned char Counter,Compare;

void Motor_Init(void)
{
	Timer1_Init();
}

void Motor_SetSpeed(unsigned char Speed)
{
	Compare = Speed;
}

//	计时器1中断函数模板
void Timer1_Routine(void) interrupt 3
{
	TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	++Counter;
	if(Counter >= 100)
		Counter = 0;
	if(Counter < Compare)
		Motor = 1;
	else
		Motor = 0;
}