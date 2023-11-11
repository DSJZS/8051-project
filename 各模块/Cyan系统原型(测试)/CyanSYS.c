#include "CyanSYS.h"

/**
	*@brief		Cyan系统循环，用于按时调动系统各部分，周期为 1ms
  *@param		无
  *@retval	无
  **/
static void CyanSYS_Loop(void)
{
	static unsigned int KeyCount;	//	独立按键计时
	
	++KeyCount;
	if(KeyCount >= KEY_LOOP_TIME)
	{
		KeyCount = 0;
		Key_Loop();	//	执行独立按键循环
	}

}

/**
	*@brief		Cyan系统执行函数，为定时器0的中断函数
  *@param		无
  *@retval	无
  **/
static void CyanSYS_Proc(void) interrupt 1
{
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	
	CyanSYS_Loop();		//	Cyan系统循环
}

/**
  *@brief		Cyan系统初始化(消息队列初始化、...)
  *@param		无
  *@retval	无
  **/
void CyanSYS_Init(void)
{
	MSG_InitQueue();	//	初始化消息队列
	Timer0_Init();		//	初始化计时器0
}