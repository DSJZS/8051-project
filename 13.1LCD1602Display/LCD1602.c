#include "LCD1602.h"

sbit LCD_EN = P2^7;
sbit LCD_RS = P2^6;
sbit LCD_WR = P2^5;
#define LCD_DataPort P0

/**
  *@brief		
  *@param		
  *@retval	
  **/
static void LCD_Delay(void)	//@11.0592MHz延时 1ms
{
	unsigned char data i, j;
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

/**
  *@brief		
  *@param		
  *@retval	
  **/
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;							//	RS置低电平表示指令
	LCD_WR = 0;							//	WR置低电平表示写入
	LCD_DataPort = Command;	//	将要写入的指令放到数据端口上
	LCD_EN = 1;							//	使数据有效(送入数据)
	LCD_Delay();						//	延时使数据能够完整写入
	LCD_EN = 0;							//	执行命令
	LCD_Delay();						//	延时使数据能够完整写入
}

/**
  *@brief		
  *@param		
  *@retval	
  **/
void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;							//	RS置高电平表示数据
	LCD_WR = 0;							//	WR置低电平表示写入
	LCD_DataPort = Data;		//	将要写入的数据放到数据端口上
	LCD_EN = 1;							//	使数据有效(送入数据)
	LCD_Delay();						//	延时使数据能够完整写入
	LCD_EN = 0;							//	执行命令
	LCD_Delay();						//	延时使数据能够完整写入
}

/**
  *@brief		
  *@param		
  *@retval	
  **/
void LCD_SetCursor(unsigned char Row,unsigned char Col)
{
	if(Row == 1)
	{
		LCD_WriteCommand(0x80 | (Col-1));
	}
	else if(Row == 2)
	{
		LCD_WriteCommand(0x80 | (0x40+Col-1));
	}
}
/**
  *@brief		
  *@param		
  *@retval	
  **/
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);	// 八位数据接口，两行显示，5x7点阵
	LCD_WriteCommand(0x0C);	// 显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);	// 显示开，光标关，闪烁关
	LCD_WriteCommand(0x01);	// 清屏
}

/**
  *@brief		
  *@param		
  *@retval	
  **/
void LCD_ShowChar(unsigned char Row,unsigned char Col,unsigned char Char)
{
	LCD_SetCursor(Row,Col);
	LCD_WriteData(Char);
}

/**
  *@brief		
  *@param		
  *@retval	
  **/
void LCD_ShowString(unsigned char Row,unsigned char Col,unsigned char* String)
{
	unsigned char i = 0;
	LCD_SetCursor(Row,Col);
	for(i=0;String[i];++i)
	{
		LCD_WriteData(String[i]);
	}
}

static int LCD_Pow(int X,int Y)
{
	int ret = 1;
	if(Y>=0)
	{
		while(Y--)
		{
			ret *= X;
		}
	}
	return ret;
}

void LCD_ShowNum(unsigned char Row,unsigned char Col,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	LCD_SetCursor(Row,Col);
	for(i=Length;i>0;--i)
	{
		LCD_WriteData('0' + Number/LCD_Pow(10,i-1)%10);
	}
}

void LCD_ShowSignedNum(unsigned char Row,unsigned char Col,int Number,unsigned char Length)
{
	unsigned char i = 0;
	unsigned int num = 0;
	LCD_SetCursor(Row,Col);
	if(Number>0)
	{
		LCD_WriteData('+');
		num = Number;
	}
	else if(Number<0)
	{
		LCD_WriteData('-');
		num = -Number;
	}
	for(i=Length;i>0;--i)
	{
		LCD_WriteData(num/LCD_Pow(10,i-1)%10+'0');
	}
}

void LCD_ShowHexNum(unsigned char Row,unsigned char Col,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	unsigned char SingleNumber = 0;
	LCD_SetCursor(Row,Col);
	for(i=Length;i>0;--i)
	{
		SingleNumber = Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber < 10)
			LCD_WriteData('0' + SingleNumber);
		else
			LCD_WriteData('A' + SingleNumber -10);
	}
}

void LCD_ShowBinNum(unsigned char Row,unsigned char Col,unsigned int Number,unsigned char Length)
{
	unsigned char i = 0;
	LCD_SetCursor(Row,Col);
	for(i=Length;i>0;--i)
	{
		LCD_WriteData('0' + Number/LCD_Pow(2,i-1)%2);
	}
}