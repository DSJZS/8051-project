#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "IR.h"


unsigned char Num;
unsigned int Address;
unsigned int Command;

void main()
{
	LCD_Init();
	IR_Init();
	LCD_ShowString(1,1,"ADDR   CMD   NUM");
	LCD_ShowString(1,1,"00     00    000");

	while(1)
	{
		if( IR_GetDataFlag() || IR_GetRepeatFlag() )
		{
			Address = IR_GetAddress();
			Command = IR_GetCommand();
			LCD_ShowHexNum(2,1,Address,2);
			LCD_ShowHexNum(2,8,Command,2);
			
			if(Command == IR_VOL_MINUS)
			{
				--Num;
			}
			if(Command == IR_VOL_ADD)
			{
				++Num;
			}
			LCD_ShowNum(2,14,Num,3);
		}
	}
}

//void Int0_Routine(void) interrupt 0
//{
//	Num--;
//}