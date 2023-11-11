#ifndef __KEY_H__
#define __KEY_H__

#include <REGX52.H>
#include "Delay.h"

/*	支持同时识别多个独立按键的状态
		某一个按键只能处于单击或者长按状态	
		不同两个的按键之间可以同时处于单击状态，又或者是一个单击状态一个长按状态
*/

//	单击标识
#define KEY_P1	0x08	//	0000 1000
#define KEY_P2	0x04	//	0000 0100
#define KEY_P3	0x02	//	0000 0010
#define KEY_P4	0x01	//	0000 0001
//	长按标识
#define KEY_LP1	0x80	//	1000 0000
#define KEY_LP2	0x40	//	0100 0000
#define KEY_LP3	0x20	//	0010 0000
#define KEY_LP4	0x10	//	0001 0000

unsigned char Key(unsigned char);
void Key_Loop(void);

#endif