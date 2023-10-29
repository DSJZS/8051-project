#ifndef __BUZZER_H__
#define __BUZZER_H__

#include <REGX52.H>
#include <INTRINS.H>

sbit Buzzer = P2^5;

void Buzzer_Time(unsigned int xms);

#endif