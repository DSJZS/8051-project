#ifndef __CYANSYS_H__
#define __CYANSYS_H__

#include "MSG.h"
#include "Key.h"
#include "Timer0.h"

/*	为自创的简易系统的初步版本
	此系统即可叫做“青色系统”，也可"cya棒棒棒系统"(bushi)
	会占用定时器0用以系统运行
*/

/*
	目前仅实现了消息队列和独立按键的检测
*/

void CyanSYS_Init(void);

#endif