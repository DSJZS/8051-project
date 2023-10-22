#include "UART.h"

/**
  *@brief		串口初始化，4800bps@11.0592MHz
  *@param		无
  *@retval	无
  **/
void UART_Init(void)		
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;			//设置定时初始值
	TH1 = 0xF4;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	
	EA = 1;		//	启用中断
	ES = 1;		//	启动串口中断
}

/**
  *@brief		串口发送一字节数据
  *@param		Byte 要发送的一个字节数据
  *@retval	无
  **/
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;	//	发送数据
	
	while(TI==0);	//	确保数据发送完全
	
	TI=0;
}


/*	串口中断模板
void UART_Rounting() interrupt 4
{
	if(RI==1)
	{
		P2 = SBUF;
		UART_SendByte(SBUF);
		RI = 0;
	}
}
*/