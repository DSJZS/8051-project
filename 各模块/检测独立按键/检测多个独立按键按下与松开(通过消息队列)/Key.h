#ifndef __KEY_H__
#define __KEY_H__

/*
	该模块用于发出独立按键消息，每个按键消息结构体包含如下信息
	message - 独立按键消息
	param	  - 独立按键键码
	count		-	重复计数
*/

#include <REGX52.H>
#include "MSG.h"

#define KEY_LOOP_TIME 20	//	每两次Key_Loop函数执行间隔(单位为ms)

void Key_Loop(void);

#endif