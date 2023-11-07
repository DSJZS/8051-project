#ifndef __ONEWIRE_H__
#define __ONEWIRE_H__

#include <REGX52.H>
#include "Delay.h"

/*
注意：这些函数执行过程会关闭中断，可能产生影响
*/

unsigned char OneWire_Init(void);
void OneWire_SendBit(unsigned char Bit);
unsigned char OneWire_ReceiveBit(void);
void OneWire_SendByte(unsigned char Byte);
unsigned char OneWire_ReceiveByte(void);

#endif