#include "Timer0.h"

//void Timer0_Init()
//{
//	//	TMOD = 0x01;	//	0000 0001	会影响T1
//	
//	//	所谓与或式赋值法
//	TMOD &= 0xF0;	//	把TMOD低四位清零，高四位保持不变
//	TMOD |= 0x01;	//	把TMOD低四位设置，高四位保持不变
//	
//	TF0 = 0;	//	初始化溢出标识
//	TR0 = 1;	//	让T0开始工作
//	
//	TH0 = 64536/256;	//	为计时器赋初值，达到计时1ms的效果
//	TL0 = 64536%256;
//	
//	EA = 1;		//	CPU对外开放中断
//	ET0 = 1;	//	CPU对T0开放中断

//	PT0 = 0;	//	设置优先级为0(最低优先级)
//}

void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	EA = 1;			//	CPU对外开放中断
	ET0 = 1;		//	CPU对T0开放中断
	PT0 = 0;	//	设置优先级为0(最低优先级)
}

//	计时器0中断函数模板，适用于 11.0592MHZ下每1ms的循环
//void Timer0_Routine(void) interrupt 1
//{
//	static unsigned int T0count;
//
//	TL0 = 0x66;				//设置定时初始值
//	TH0 = 0xFC;				//设置定时初始值
//	++T0count;
//
//	if(T0count % 1000 == 0)
//	{
//		T0count = 0;	
//	}
//}