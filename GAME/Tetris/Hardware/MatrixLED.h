#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

#include <REGX52.H>
#include "Delay.h"

//	此处 ^ 并非异或，是表示第几位
sbit RCK=P3^5;	//	RCLK	-	寄存器时钟
sbit SCK=P3^6;	//	SRCLK	-	串行时钟
sbit SER=P3^4;	//	SER		-	串行

#define MATRIX_LED_PORT	P0

void _74HC595_WriteByte(unsigned char Byte);
void MatrixLED_ShowColum(unsigned char Col,Data);
void MatrixLED_ShowRow(unsigned char Row,Data);
void MatrixLED_Init(void);

#endif