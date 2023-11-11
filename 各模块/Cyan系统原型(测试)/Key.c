#include "Key.h"

/*	按键标识位，1-8位分别用于表示不同的按键消息
*/
static unsigned char Key_Press=0;

#define KEY_P1	0x01	//	0000 0001
#define KEY_P2	0x02	//	0000 0010
#define KEY_P3	0x04	// 	0000 0100
#define KEY_P4	0x08	//	0000 1000

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
  *@brief		将按键的物理状态转为按键消息发送
  *@param		无
  *@retval	无
  **/
static void Key_SendMessage(void)
{
	//	按键状态记录
	static unsigned char LastState,NowState;	
	MSG msg = {	0,0,0};
	LastState = NowState;			//	记录上一次的按键状态
	NowState = Key_GetState();//	将物理按键状态计入本次按键状态
	
	//	发出独立按键松开消息
	if((LastState	& KEY_P1) && !(NowState & KEY_P1))
	{	
		msg.message = VK_INDBTN_UP;
		msg.param = 1;
		MSG_SendMessage(&msg);
	}
	if((LastState & KEY_P2) && !(NowState & KEY_P2))
	{	
		msg.message = VK_INDBTN_UP;
		msg.param = 2;
		MSG_SendMessage(&msg);
	}
	if((LastState & KEY_P3) && !(NowState & KEY_P3))
	{	
		msg.message = VK_INDBTN_UP;
		msg.param = 3;
		MSG_SendMessage(&msg);
	}
	if((LastState & KEY_P4) && !(NowState & KEY_P4))
	{	
		msg.message = VK_INDBTN_UP;
		msg.param = 4;
		MSG_SendMessage(&msg);
	}
	//	发出独立按键按下消息
	if(NowState & KEY_P1)
	{	
		msg.message = VK_INDBTN_DOWN;
		msg.param = 1;
		MSG_SendMessage(&msg);
	}
	if(NowState & KEY_P2)
	{	
		msg.message = VK_INDBTN_DOWN;
		msg.param = 2;
		MSG_SendMessage(&msg);
	}
	if(NowState & KEY_P3)
	{	
		msg.message = VK_INDBTN_DOWN;
		msg.param = 3;
		MSG_SendMessage(&msg);
	}
	if(NowState & KEY_P4)
	{	
		msg.message = VK_INDBTN_DOWN;
		msg.param = 4;
		MSG_SendMessage(&msg);
	}
}

/**
	*@brief		外部接口，用于在外部定时器中断函数中不断执行以发送按键消息，推荐以20ms为周期执行
  *@param		无
  *@retval	无
  **/
void Key_Loop(void)
{
	Key_SendMessage();
}