#include "I2C.h"
/**
  *@brief		I2C开始
  *@param		无
  *@retval	无
  **/
void I2C_Start(void)
{
	I2C_SDA = 1;	//	SCL低电平时才能变换数据
	I2C_SCL = 1;	//	数据变换后拉SCL高电平
	I2C_SDA = 0;	//	在SCL为高电平时拉低SDA，启动
	I2C_SCL = 0;	//	最后拉低SCL电平
}

/**
  *@brief		I2C停止
  *@param		无
  *@retval	无
  **/
void I2C_Stop(void)
{
	I2C_SDA = 0;	//	SCL低电平时才能变换数据
	I2C_SCL = 1;	//	数据变换后拉SCL高电平
	I2C_SDA = 1;	//	在SCL为低电平时拉高SDA，停止
}

/**
  *@brief		I2C发送一个字节
  *@param		Byte	要发送的字节
  *@retval	无
  **/
void I2C_SendByte(unsigned char Byte)
{
	int i = 0;
	for(i=0;i<8;++i)	//	循环八次，每一次发送一个bit位
	{	
		I2C_SDA = ( Byte & (0x80 >> i) );	//	从高位开始发送
		I2C_SCL = 1;	//	时钟拉高
		I2C_SCL = 0;	//	时钟拉低
	}
}

/**
  *@brief		I2C接收一个字节
  *@param		无
  *@retval	接受到的一个字节数据
  **/
unsigned char I2C_ReceiveByte(void)
{
	unsigned char Byte=0x00,i=0x00;
	I2C_SDA = 1;	//	主机释放 SDA
	for(i=0;i<8;++i)	//	循环八次，每一次接收一个bit位
	{
		I2C_SCL = 1;	//	时钟拉高
		if(I2C_SDA == 1){	Byte |= (0x80>>i);}	//	(根据协议在SCL高位时)从高位开始接收(SCL低位其实也能接收)
		I2C_SCL = 0;	//	时钟拉低
	}
	return Byte;	//	返回接收的数据
}

/**
  *@brief		I2C发送应答
	*@param		AckBit	应答位，0为应答，1为非应答
  *@retval	无
  **/
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA = AckBit;	//	发送应答位
	I2C_SCL = 1;	//	时钟拉高
	I2C_SCL = 0;	//	时钟拉低
}

/**
  *@brief		I2C接收应答
  *@param		无
  *@retval	接收到的应答位，0为应答，1为非应答
  **/
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit = 0x00;
	I2C_SDA = 1;	//	主机释放 SDA
	I2C_SCL = 1;	//	时钟拉高
	AckBit = I2C_SDA;	//	(根据协议在SCL高位时)从高位开始接收(SCL低位其实也能接收)
	I2C_SCL = 0;	//	时钟拉低
	return AckBit;	//	返回接收的应答位
}