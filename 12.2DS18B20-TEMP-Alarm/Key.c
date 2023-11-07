#include "Key.h"

//	按键标识位，标识当前被识别按下的按键键码
unsigned char Key_Press=0;

/**
  *@brief		获取独立按键键码
  *@param		无
  *@retval	按下按键的键码，范围：0-4，无按键按下时返回0
  **/
//unsigned char Key(void)
//{
//	unsigned char KeyNum=0;
//	if(P3_1 == 0){Delay(20);	while(P3_1 == 0);	Delay(20);	KeyNum=1;	}
//	if(P3_0 == 0){Delay(20);	while(P3_0 == 0);	Delay(20);	KeyNum=2;	}
//	if(P3_2 == 0){Delay(20);	while(P3_2 == 0);	Delay(20);	KeyNum=3;	}
//	if(P3_3 == 0){Delay(20);	while(P3_3 == 0);	Delay(20);	KeyNum=4;	}
//	return KeyNum;
//}

/**
  *@brief		用于外部根据按键标识位获取独立按键键码，并且置空按键标识位
  *@param		无
  *@retval	按下按键的键码，范围：0-4，无按键按下时返回0
  **/
unsigned char Key(void)
{
	unsigned char Tmp = Key_Press;
	Key_Press = 0;
	return Tmp;
}

/**
  *@brief		获取当前按键信息
  *@param		无
  *@retval	当前按键键码，范围：0-4，无按键按下时返回0
  **/
unsigned char Key_GetState(void)
{
	unsigned char KeyNum=0;
	
	if(P3_1 == 0){KeyNum=1;	}
	if(P3_0 == 0){KeyNum=2;	}
	if(P3_2 == 0){KeyNum=3;	}
	if(P3_3 == 0){KeyNum=4;	}
	
	return KeyNum;
}

/**
  *@brief		用于在定时器中断函数中扫描各个独立按键，推荐以20ms为周期执行
  *@param		无
  *@retval	无
  **/
void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState = NowState;
	NowState = Key_GetState();
	
	
	if((LastState==1)&&(NowState==0)){	Key_Press=1;}
	if((LastState==2)&&(NowState==0)){	Key_Press=2;}
	if((LastState==3)&&(NowState==0)){	Key_Press=3;}
	if((LastState==4)&&(NowState==0)){	Key_Press=4;}
}