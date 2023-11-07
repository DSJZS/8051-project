#include "AT24C02.h"

#define AT24C02_ADDRESS 0xA0

/**
  *@brief		AT24C02写入一个字节
  *@param		WordAddress	要写入字节的地址
  *@param		Data	要写入的数据
  *@retval	无
  **/
void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();	//	开始
	I2C_SendByte(AT24C02_ADDRESS);	//	发送从机地址(写)
	I2C_ReceiveAck();								//	默认成功，可按需求修改
	I2C_SendByte(WordAddress);			//	发送字地址
	I2C_ReceiveAck();								//	默认成功，可按需求修改
	I2C_SendByte(Data);							//	发送数据
	I2C_ReceiveAck();								//	默认成功，可按需求修改
	I2C_Stop();	//	结束
}

/**
  *@brief		AT24C02读取一个字节
  *@param		WordAddress	要读取字节的地址
  *@retval	读取的数据
  **/
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	
	I2C_Start();	//	开始
	I2C_SendByte(AT24C02_ADDRESS);	//	发送从机地址(写 )
	I2C_ReceiveAck();											//	默认成功，可按需求修改
	I2C_SendByte(WordAddress);						//	发送字地址
	I2C_ReceiveAck();											//	默认成功，可按需求修改
	
	I2C_Start();	//	开始
	I2C_SendByte(AT24C02_ADDRESS | 0x01);	//	发送从机地址(读)
	I2C_ReceiveAck();											//	默认成功，可按需求修改
	Data = I2C_ReceiveByte();							//	接收数据
	I2C_SendAck(1);												//	默认为不应答
	I2C_Stop();	//	结束
	
	return Data;
}
