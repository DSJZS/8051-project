#include "INT0.h"
#include <REGX52.H>

void Int0_Init(void)
{
	IT0 = 1;	//	设置下降沿触发模式
	IE0 = 0;	//	初始化外部中断标志
	EX0 = 1;	//	外部中断使能打开
	EA  = 1;	//	允许中断
	PX0 = 1;	//	较高优先级，确保优先接受红外信号
}

/*
void Int0_Routine(void) interrupt 0
{
}
*/ 