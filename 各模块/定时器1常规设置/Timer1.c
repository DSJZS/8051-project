#include "Timer1.h"

void Timer1_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0x0F;			//设置定时器模式
	TMOD |= 0x10;			//设置定时器模式
	TL1 = 0xA4;				//设置定时初始值
	TH1 = 0xFF;				//设置定时初始值
	TF1 = 0;				//清除TF1标志
	TR1 = 1;				//定时器1开始计时
	EA = 1;			//	CPU对外开放中断
	ET1 = 1;		//	CPU对T1开放中断
	PT1 = 0;	//	设置优先级为0(最低优先级)
}

//	计时器1中断函数模板，适用于 11.0592MHZ下每1ms的循环
//void Timer1_Routine(void) interrupt 3
//{
//	static unsigned int T1count;
//
//	TL1 = 0x66;				//设置定时初始值
//	TH1 = 0xFC;				//设置定时初始值
//	++T1count;
//
//	if(T1count % 1000 == 0)
//	{
//		T1count = 0;	
//	}
//}