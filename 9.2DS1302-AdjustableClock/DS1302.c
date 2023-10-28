#include "DS1302.h"


//时间数组，索引0~6分别为年、月、日、时、分、秒、星期
char DS1302_Time[] = {23,10,28,12,49,0,6};

/**
  *@brief		往DS1302通过命令字写入BCD码数据
  *@param		Command	命令字	Data	BCD码数据
  *@retval	无
  **/
void DS1302_WriteByte(unsigned char Command,Data)
{
	unsigned char i = 0;
	DS1302_CE = 1;	//	打开使能，使IO能够写入数据
	
	for(i=0;i<8;++i)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	
	for(i=0;i<8;++i)
	{
		DS1302_IO = Data & (0x01<<i);
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	
	DS1302_CE = 0;	//	关闭使能
}	

/**
  *@brief		从DS1302通过命令字读出BCD码数据
  *@param		Command	命令字
  *@retval	读出的BCD码数据
  **/
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i = 0;
	unsigned char Data = 0x00;
	DS1302_CE = 1;	//	打开使能，使IO能够读取数据
	Command |= 0x01;	//	使Command最低位为 1
	for(i=0;i<8;++i)
	{
		DS1302_IO = Command & (0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	
	for(i=0;i<8;++i)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO)
			Data |= (0x01<<i);
	}
	
	DS1302_CE = 0;	//	关闭使能
	DS1302_IO=0;	//读取后将IO设置为0，否则读出的数据会出错
	return Data;
}

/**
  *@brief		初始化DS1302
  *@param		无
  *@retval	无
  **/
void DS1302_Init(void)
{
	DS1302_CE = 0;	//	关闭使能
	DS1302_SCLK = 0;
}

/**
  *@brief		设置DS1302时间
  *@param		无
  *@retval	无
  **/
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);	//	解除芯片写入保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);	//	打开芯片写入保护
}

/**
  *@brief		读取DS1302时间
  *@param		无
  *@retval	无
  **/
void DS1302_ReadTime(void)
{
	unsigned char tmp=0;
	tmp = DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0] = tmp/16*10+tmp%16;
	tmp = DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1] = tmp/16*10+tmp%16;
	tmp = DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2] = tmp/16*10+tmp%16;
	tmp = DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3] = tmp/16*10+tmp%16;
	tmp = DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4] = tmp/16*10+tmp%16;
	tmp = DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5] = tmp/16*10+tmp%16;
	tmp = DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6] = tmp/16*10+tmp%16;
}