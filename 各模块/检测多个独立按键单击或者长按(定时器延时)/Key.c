#include "Key.h"

//	长按响应时间(以Key_Loop函数执行次数记录)
#define KEY_LP_RESPONSE 50
//	消息队列对头信息最长响应时间(以Key_Loop函数执行次数记录)
#define KEY_CLR_RESPONSE 10

/*	按键标识位，1-8位分别用于表示不同的按键消息
	第1位和第5位分别表示按键1的长按与按下消息
	第2位和第6位分别表示按键2的长按与单击消息
	第3位和第7位分别表示按键3的长按与单击消息
	第4位和第8位分别表示按键4的长按与单击消息
*/
static unsigned char Key_Message=0;

//	按键状态记录
static unsigned char LastState,NowState;	

/**
	*@brief		用于外部判断独立按键是否为某一个状态
  *@param		KeyNum	需要被判断的按键状态，由单个按键标识或者多个按键标识或操作组成
  *@retval	实际按键状态与KeyNum相符合返回 1，否则返回 0
  **/
unsigned char Key(unsigned char KeyNum)
{
	if((Key_Message & KeyNum) == KeyNum)
	{
		Key_Message &= ~(KeyNum);
		return 1;
	}
	else
	{
		return 0;
	}
}

/**
  *@brief		获取当前按键的物理状态
  *@param		无
  *@retval	当前按键物理状态，无按键按下时返回0
  **/
static unsigned char Key_GetState(void)
{
	unsigned char KeyNum=0;
	
	if(P3_1 == 0){	KeyNum|=KEY_P1;	}
	if(P3_0 == 0){	KeyNum|=KEY_P2;	}
	if(P3_2 == 0){	KeyNum|=KEY_P3;	}
	if(P3_3 == 0){	KeyNum|=KEY_P4;	}
	return KeyNum;
}


/**
  *@brief		利用按键状态判断是否发出按键长按消息，对其按键长按标志位进行处理
  *@param		当前按键
  *@retval	
  **/
static void Key_LPress()
{
	static unsigned int LP1Cnt,LP2Cnt,LP3Cnt,LP4Cnt;	//	长按消息计数变量
	//	长按消息计数
	if(NowState & KEY_P1){	++LP1Cnt; }	else{	LP1Cnt=0; }
	if(NowState & KEY_P2){	++LP2Cnt; }	else{	LP2Cnt=0; }
	if(NowState & KEY_P3){	++LP3Cnt; }	else{	LP3Cnt=0; }
	if(NowState & KEY_P4){	++LP4Cnt; }	else{	LP4Cnt=0; }
	//	发出长按信息
	if(LP1Cnt >= KEY_LP_RESPONSE)
	{	Key_Message |= KEY_LP1;	NowState |= KEY_LP1;	LP1Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Message &= (~KEY_LP1);	}
	if(LP2Cnt >= KEY_LP_RESPONSE)
	{	Key_Message |= KEY_LP2;	NowState |= KEY_LP2;	LP2Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Message &= (~KEY_LP2);	}
	if(LP3Cnt >= KEY_LP_RESPONSE)
	{	Key_Message |= KEY_LP3;	NowState |= KEY_LP3;	LP3Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Message &= (~KEY_LP3);	}
	if(LP4Cnt >= KEY_LP_RESPONSE)
	{	Key_Message |= KEY_LP4;	NowState |= KEY_LP4;	LP4Cnt = KEY_LP_RESPONSE;	}
	else{	Key_Message &= (~KEY_LP4);	}
}

/**
  *@brief		利用按键状态判断是否发出按键单击消息，对其按键单击标志位进行处理
  *@param		无
  *@retval	无
  **/
static void Key_Press()
{
	static unsigned int Btn1Cnt,Btn2Cnt,Btn3Cnt,Btn4Cnt;	//	单击消息未响应计数变量
	//	单击消息未响应计数
	if(Key_Message & KEY_P1){	++Btn1Cnt;	}
	else{	Btn1Cnt=0;	}
	if(Key_Message & KEY_P2){	++Btn2Cnt;	}
	else{	Btn2Cnt=0;	}
	if(Key_Message & KEY_P3){	++Btn3Cnt;	}
	else{	Btn3Cnt=0;	}
	if(Key_Message & KEY_P4){	++Btn4Cnt;	}
	else{	Btn4Cnt=0;	}
	//	去除长时间未响应的单击消息
	if(Btn1Cnt >= KEY_CLR_RESPONSE){	Key_Message &= (~KEY_P1);	}
	if(Btn2Cnt >= KEY_CLR_RESPONSE){	Key_Message &= (~KEY_P2);	}
	if(Btn3Cnt >= KEY_CLR_RESPONSE){	Key_Message &= (~KEY_P3);	}
	if(Btn4Cnt >= KEY_CLR_RESPONSE){	Key_Message &= (~KEY_P4);	}
	//	发出单击消息
	if((LastState	& KEY_P1) && !(LastState & KEY_LP1) && !(NowState & KEY_P1))
	{	Key_Message |= KEY_P1;	}
	if((LastState & KEY_P2) && !(LastState & KEY_LP2) && !(NowState & KEY_P2))
	{	Key_Message |= KEY_P2;	}
	if((LastState & KEY_P3) && !(LastState & KEY_LP3) && !(NowState & KEY_P3))
	{	Key_Message |= KEY_P3;	}
	if((LastState & KEY_P4) && !(LastState & KEY_LP4) && !(NowState & KEY_P4))
	{	Key_Message |= KEY_P4;	}
}

/**
  *@brief		将按键的物理状态转为按键消息
  *@param		无
  *@retval	无
  **/
static void Key_SetMessage(void)
{
	LastState = NowState;			//	记录上一次的按键状态
	NowState = Key_GetState();//	将物理按键状态计入本次按键状态
	
	Key_Press();	//	利用按键状态判断是否发出按键单击消息
	Key_LPress();	//	利用按键状态判断是否发出按键长按消息
}

/**
	*@brief		外部接口，用于在外部定时器中断函数中不断获取按键消息，推荐以20ms为周期执行
  *@param		无
  *@retval	无
  **/
void Key_Loop(void)
{
	Key_SetMessage();
}