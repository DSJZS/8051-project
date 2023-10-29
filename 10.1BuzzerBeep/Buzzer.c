#include "Buzzer.h"

/**
  *@brief		蜂鸣器私有函数，延时500us
  *@param		无
  *@retval	无
  **/
static void Buzzer_Delay500us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 227;
	while (--i);
}

/**
  *@brief		蜂鸣器发声
  *@param		xms 	发声的时间，单位毫秒
  *@retval	无
  **/
void Buzzer_Time(unsigned int xms)
{
	unsigned int i = 0;
	for(i=0;i<xms*2;++i)
	{
		Buzzer = !Buzzer;
		Buzzer_Delay500us();
	}
}