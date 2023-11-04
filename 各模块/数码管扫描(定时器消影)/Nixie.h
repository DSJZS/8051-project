#ifndef __NIXIE_H__
#define __NIXIE_H__

#include <REGX52.H>
#include <Delay.h>

void Nixie_SetBuf(unsigned char Location,unsigned char Number);
void Nixie_Scan(unsigned char Location,unsigned char Number);
void Nixie_Loop(void);

#endif