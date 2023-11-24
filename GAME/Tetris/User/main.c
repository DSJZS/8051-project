#include <REGX52.H>
#include "Tetris.h"
#include "Timer0.h"
#include "Key.h"

unsigned char KeyNum = 0;

void main()
{
	Tetris_Init();
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			//isPause = 1;
			switch(KeyNum)
			{
			case 1:
				Tetris_ToLeft();
				break;
			case 2:
				Tetris_ToRight();
				break;
			case 3:
				Tetris_RtLeft();
				break;
			case 4:
				Tetris_RtRight();
				break;
			default:
				break;
			}
		}
		Tetris_Display();
	}
}

void Timer0_Routine(void) interrupt 1
{
	static unsigned int T_Key_Count,T_Fall_Count;

	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	++T_Key_Count;
	++T_Fall_Count;

	if(T_Key_Count >= 20)
	{
		T_Key_Count = 0;
		Key_Loop();		
	}
	
	if(T_Fall_Count >= 700)
	{
		T_Fall_Count = 0;
		if( !Tetris_Fall() )
		{
			Tetris_Stack();
			if(Tetris_GameOver())
			{
				TR0 = 0;
				Delay(1000);
				Tetris_Init();
				TR0 = 1;
			}
			else
			{
				Tetris_Full();
				Tetris_Create();
			}
		}
	}
}