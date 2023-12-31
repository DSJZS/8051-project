#ifndef __DS1302_H__
#define __DS1302_H__

#include <REGX52.H>

sbit DS1302_SCLK = P3^6;
sbit DS1302_IO = P3^4;
sbit DS1302_CE = P3^5;

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR	 	0x84
#define DS1302_DATE		0x86
#define DS1302_MONTH	0x88
#define DS1302_DAY		0x8A
#define DS1302_YEAR		0x8C
#define DS1302_WP			0x8E

extern unsigned char DS1302_Time[];

void DS1302_WriteByte(unsigned char Command,Data);

unsigned char DS1302_ReadByte(unsigned char Command);

void DS1302_Init(void);

void DS1302_SetTime(void);

void DS1302_ReadTime(void);

#endif