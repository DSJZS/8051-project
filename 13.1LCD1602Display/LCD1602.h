#ifndef __LCD1602_H__
#define __LCD1602_H__

#include <REGX52.H>
#include <INTRINS.h>

void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Init(void);
void LCD_ShowChar(unsigned char Row,unsigned char Col,unsigned char Char);
void LCD_ShowString(unsigned char Row,unsigned char Col,unsigned char* String);
void LCD_ShowNum(unsigned char Row,unsigned char Col,unsigned int Number,unsigned char Length);
void LCD_ShowSignedNum(unsigned char Row,unsigned char Col,int Number,unsigned char Length);
void LCD_ShowHexNum(unsigned char Row,unsigned char Col,unsigned int Number,unsigned char Length);
void LCD_ShowBinNum(unsigned char Row,unsigned char Col,unsigned int Number,unsigned char Length);

#endif