#include "XPT2046.h"
#include <REGX52.H>

sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;

unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i = 0;
	unsigned int ADValue = 0;
	XPT2046_DCLK = 0;					//	初始化时钟，置低电平
	XPT2046_CS = 0;						//	开始，片选置低电平
	for(i=0;i<8;++i)					//	发送8位命令
	{
		XPT2046_DIN = Command & (0x80>>i);
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
	}
	for(i=0;i<16;++i)					//	接受2字节AD数据
	{
		XPT2046_DCLK = 1;
		XPT2046_DCLK = 0;
		if(XPT2046_DOUT)
			ADValue |= (0x8000>>i);
	}
	XPT2046_CS = 1;						//	结束，片选置高电平
	if(Command & 0x08)
		return ADValue>>8;
	else
		return ADValue>>4;
}