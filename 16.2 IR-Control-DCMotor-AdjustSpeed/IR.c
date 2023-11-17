#include "IR.h"
#include "INT0.h"
#include <REGX52.H>
#include "Timer0.h"

unsigned int IR_Time;
unsigned char IR_State;

unsigned char IR_Date[4];
unsigned char IR_pDate;

unsigned char IR_DataFlag;
unsigned char IR_RepeatFlag;
unsigned char IR_Address;
unsigned char IR_Command;

void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();
}

unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag = 0;
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

void Int0_Routine(void) interrupt 0
{
	if(IR_State == 0)	//状态0：开始
	{
		Timer0_SetCounter(0);
		Timer0_Run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)	//状态1：判断是 Start	还是 Repeat
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time > 11982 && IR_Time < 12903)	// 11.0592MHZ下，13500-500us ~ 13500+500us内
		{
			IR_State = 2;
		}
		else if(IR_Time > 9908 && IR_Time < 10829)	// 11.0592MHZ下，11250-500us ~ 11250+500us内
		{
			IR_RepeatFlag = 1;
			Timer0_Run(0);
			IR_State = 0;
		}
		else
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)	//状态2：解码获取数据
	{
		IR_Time = Timer0_GetCounter();
		Timer0_SetCounter(0);
		if(IR_Time > 571 && IR_Time < 1493)	// 11.0592MHZ下，1120-500us ~ 1120+500us内
		{
			IR_Date[IR_pDate/8] &= ~(0x01 << (IR_pDate%8));
			++IR_pDate;
		}
		else if(IR_Time > 1613 && IR_Time < 2523)	// 11.0592MHZ下，2250-500us ~ 2250+500us内
		{
			IR_Date[IR_pDate/8] |= (0x01 << (IR_pDate%8));
			++IR_pDate;
		}
		else
		{
			IR_pDate = 0;
			IR_State = 1;
		}
		if(IR_pDate >= 32)
		{
			IR_pDate = 0;
			if( ( IR_Date[0] == ~IR_Date[1] ) && ( IR_Date[2] == ~IR_Date[3] ) )
			{
				IR_Address = IR_Date[0];
				IR_Command = IR_Date[2];
				IR_DataFlag = 1;
			}
			Timer0_Run(0);
			IR_State = 0;
		}
	}
}