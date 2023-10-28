#include "MatrixLED.h"

/**
  *@brief		点阵屏初始化
  *@param		无
  *@retval	无
  **/
void MatrixLED_Init(void)
{
	SCK = 0;
	RCK = 0;
}

/**
  *@brief		74HC595写入一个字节
  *@param		Byte	要写入的字节
  *@retval	无
  **///
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i = 0;
	for(i=0;i<8;++i)
	{
		SER = Byte&(0x80>>i);	//	非0即1
		SCK = 1;
		SCK = 0;
	}
	RCK = 1;
	RCK = 0;
	
}

/**
  *@brief		LED点阵屏显示一列数据
  *@param		Col 	要选择的列，范围：0-7，0在左边
	*@param		Data 	列显示的段码，高位在上，1为亮，0为灭
  *@retval	无
  **/
void MatrixLED_ShowColum(unsigned char Col,Data)
{
	_74HC595_WriteByte(Data);
	MATRIX_LED_PORT = ~(0x80>>Col);
	Delay(1);
	MATRIX_LED_PORT = 0xff;
}

/**
  *@brief		LED点阵屏显示一行数据
	*@param		Col 	要选择的行，范围：0-7，0在上边
	*@param		Data 	列显示的段码，高位在左，1为亮，0为灭
  *@retval	无
  **/
void MatrixLED_ShowRow(unsigned char Row,Data)
{
	_74HC595_WriteByte((0x80>>Row));
	
//	Data = ((Data & 0xAA) >> 1) | ((Data & 0x55) << 1);
//	Data = ((Data & 0xCC) >> 2) | ((Data & 0x33) << 2);
//	Data = (Data >> 4) | (Data << 4);
	
	MATRIX_LED_PORT = ~Data;
	Delay(1);
	_74HC595_WriteByte(0x00);
}

