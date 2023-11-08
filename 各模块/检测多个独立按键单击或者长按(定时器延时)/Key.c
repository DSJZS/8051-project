#include "Key.h"

//	按键标识位，标识当前被识别按下的按键键码，以及其是否长按
//	1-8位，第1位和5位分别为按键1的长按与按下识别
//	第2位和第6位则是按键2的长按与按下识别
//	第3位和第7位则是按键2的长按与按下识别
//	第4位和第8位则是按键2的长按与按下识别
unsigned char Key_Press=0;

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
	
	if(P3_1 == 0){	KeyNum|=KEY_P1;	}
	if(P3_0 == 0){	KeyNum|=KEY_P2;	}
	if(P3_2 == 0){	KeyNum|=KEY_P3;	}
	if(P3_3 == 0){	KeyNum|=KEY_P4;	}
	return KeyNum;
}

/**
  *@brief		用于在定时器中断函数中扫描各个独立按键的状态(单击或者长按)，推荐以20ms为周期执行
  *@param		无
  *@retval	无
  **/
void Key_Loop(void)
{
	static unsigned char NowState,LastState;	//	按键状态记录
	static unsigned int Btn1Cnt,Btn2Cnt,Btn3Cnt,Btn4Cnt;	//	长按计数变量
	LastState = NowState;
	NowState = Key_GetState();
	
	//	长按计数
	if(NowState & KEY_P1){	++Btn1Cnt; }	else{	Btn1Cnt=0; }
	if(NowState & KEY_P2){	++Btn2Cnt; }	else{	Btn2Cnt=0; }
	if(NowState & KEY_P3){	++Btn3Cnt; }	else{	Btn3Cnt=0; }
	if(NowState & KEY_P4){	++Btn4Cnt; }	else{	Btn4Cnt=0; }
	//	长按标识
	if(Btn1Cnt >= KEY_LP_RESPONSE)
	{	Key_Press |= KEY_LP1;	NowState |= KEY_LP1;	Btn1Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Press &= (~KEY_LP1);	}
	if(Btn2Cnt >= KEY_LP_RESPONSE)
	{	Key_Press |= KEY_LP2;	NowState |= KEY_LP2;	Btn2Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Press &= (~KEY_LP2);	}
	if(Btn3Cnt >= KEY_LP_RESPONSE)
	{	Key_Press |= KEY_LP3;	NowState |= KEY_LP3;	Btn3Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Press &= (~KEY_LP3);	}
	if(Btn4Cnt >= KEY_LP_RESPONSE)
	{	Key_Press |= KEY_LP4;	NowState |= KEY_LP4;	Btn4Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Press &= (~KEY_LP4);	}
	//	单击标识
	if((LastState	& KEY_P1) && !(LastState & KEY_LP1) && !(NowState & KEY_P1))
	{	Key_Press |= KEY_P1;	}
	if((LastState & KEY_P2) && !(LastState & KEY_LP2) && !(NowState & KEY_P2))
	{	Key_Press |= KEY_P2;	}
	if((LastState & KEY_P3) && !(LastState & KEY_LP3) && !(NowState & KEY_P3))
	{	Key_Press |= KEY_P3;	}
	if((LastState & KEY_P4) && !(LastState & KEY_LP4) && !(NowState & KEY_P4))
	{	Key_Press |= KEY_P4;	}
}