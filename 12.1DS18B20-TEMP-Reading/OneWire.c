#include "OneWire.h"

sbit OneWire_DQ = P3^7;

/**
  *@brief		单总线初始化
  *@param		无
  *@retval	应答位，0为有从机响应，1为无从机响应
  **/
unsigned char OneWire_Init(void)
{
	unsigned char i=0;			//	循环计数变量，用于延时
	unsigned char AckBit=0;	//	应答位
	OneWire_DQ = 1;					//	为了拉低，确保一开始总线为高电平
	OneWire_DQ = 0;					//	拉低总线电平
	i = 227;while (--i);		//	总线低电平延时大约500us，初始化
	OneWire_DQ = 1;					//	主机释放总线
	i = 29;while (--i);			//	等待从机响应，延时大约70us
	AckBit = OneWire_DQ;		//	获取响应，0为有从机响应，1为无从机响应
	i = 227;while (--i);		//	延时大约500us，从机响应
	return AckBit;					//	返回应答位
}

/**
  *@brief		单总线发送一个bit
  *@param		Bit	要发送的bit数据
  *@retval	无
  **/
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i=0;			//	循环计数变量，用于延时
	OneWire_DQ = 0;					//	拉低总线电平，因为此函数紧接在OneWire_Init()后，OneWire_DQ一开始默认为1
	i = 4;while (--i);			//	延时大约10us
	OneWire_DQ = Bit;				//	设置要发送的数据
	i = 22;while (--i);			//	延时大约50us
	OneWire_DQ = 1;					//	释放总线
}

/**
  *@brief		单总线接收一个bit
  *@param		无
  *@retval	接收到的bit数据
  **/
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char i=0;			//	循环计数变量，用于延时
	unsigned char Bit=0;
	OneWire_DQ = 0;					//	拉低总线电平
	i = 2;while (--i);			//	延时大约5us
	OneWire_DQ = 1;					//	释放总线
	i = 2;while (--i);			//	延时大约5us
	Bit = OneWire_DQ;
	i = 22;while (--i);			//	延时大约50us
	return Bit;
}

/**
  *@brief		单总线发送一个byte
  *@param		Byte	要发送的byte数据
  *@retval	无
  **/
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char i=0;			//	循环计数变量
	for(i=0;i<8;++i)
	{
		OneWire_SendBit( Byte&(0x01<<i) );	//	从最低位开始发送数据
	} 
}

/**
  *@brief		单总线接收一个Byte
  *@param		无
  *@retval	接收到的Byte数据
  **/
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char i=0;			//	循环计数变量
	unsigned char Byte=0x00;
	for(i=0;i<8;++i)
	{
		if( OneWire_ReceiveBit() )
			Byte |= (0x01<< i);	//	从最低位开始接收数据
	}
	return Byte;
}