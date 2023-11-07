#include "DS18B20.h"

#define DS18B20_SKIP_ROM 				0xCC
#define DS18B20_CONVERT_T 			0x44
#define DS18B20_READ_SCRATCHPAD	0xBE

/**
  *@brief		向DS18B20发送 CONVERT T(温度变化) 指令，温度传感器获取实时温度并存入暂存器
  *@param		无
  *@retval	无
  **/
void DS18B20_ConvertTEMP(void)
{
	OneWire_Init();												//	初始化，不处理返回值，默认有从机响应
	OneWire_SendByte(DS18B20_SKIP_ROM);		//	发送 SKIP ROM 指令
	OneWire_SendByte(DS18B20_CONVERT_T);	//	发送 CONVERT T 指令
}

/**
  *@brief		向DS18B20发送 READ SCRATCHPAD(读暂存器) 指令，从DS18B20暂存器读取温度信息
  *@param		无
  *@retval	获取的温度信息
  **/
float DS18B20_ReadTEMP(void)
{
	unsigned char TLSB,TMSB;										//	用于接受 LSB和MSB 温度数据	
	int Tmp;																		//	临时变量，用于临时存放温度信息
	float T;																		//	单精度变量，用于存放要返回的温度
	OneWire_Init();															//	初始化，不处理返回值，默认有从机响应
	OneWire_SendByte(DS18B20_SKIP_ROM);					//	发送 SKIP ROM 指令
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);	//	发送 READ SCRATCHPAD 指令
	TLSB = OneWire_ReceiveByte();								//	读取温度数据
	TMSB = OneWire_ReceiveByte();								//	读取温度数据
	Tmp = (TMSB<<8)|TLSB ;											//	获取真实温度的16倍(Tmp后四位应该是小数位)
	T = Tmp/16.0f;															//	获取真实的温度
	return T;
}