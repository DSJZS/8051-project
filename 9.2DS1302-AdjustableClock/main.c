#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer0.h"
//	KeyNum						用于记录独立按键键码
//	MODE							用于记录当前模式
//	TimeSetSelect			用于记录修改模式下修改那个时间数据
//	TimeSetFlashFlag	用于修改模式下被修改数据的闪烁
//	LastTimeSetSelect	用于记录上一个模式以消除数据提示
char KeyNum=0,MODE=0,TimeSetSelect=0,TimeSetFlashFlag=0,LastTimeSetSelect = -1;

/**
  *@brief		读取时间数据并且显示
  *@param		无
  *@retval	无
  **/
void TimeShow(void)
{
	DS1302_ReadTime();
	LCD_ShowNum(1,1,DS1302_Time[0],2);
	LCD_ShowNum(1,4,DS1302_Time[1],2);
	LCD_ShowNum(1,7,DS1302_Time[2],2);
	LCD_ShowNum(2,1,DS1302_Time[3],2);
	LCD_ShowNum(2,4,DS1302_Time[4],2);
	LCD_ShowNum(2,7,DS1302_Time[5],2);
}

/**
  *@brief		修改时间数据
  *@param		无
  *@retval	无
  **/
void TimeSet(void)
{
	if(KeyNum==2)
	{
		++TimeSetSelect;
		TimeSetSelect %= 6;
	}
	if(KeyNum==3)
	{
		++( DS1302_Time[TimeSetSelect] );
		if(DS1302_Time[0] > 99){	DS1302_Time[0] = 0;	};
		if(DS1302_Time[1] > 12){	DS1302_Time[1] = 1;	};
		
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || 
			DS1302_Time[1]==5 || DS1302_Time[1]==7 || DS1302_Time[1]==8 || 
			DS1302_Time[1]==10 ||	DS1302_Time[1]==12)
		{
			if(DS1302_Time[2] > 31)
				DS1302_Time[2] = 1;
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || 
			DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2] > 30)
				DS1302_Time[2] = 1;
		}
		else
		{
			if(DS1302_Time[0] % 4 == 0)
			{
				if(DS1302_Time[2] > 29)
					DS1302_Time[2] = 1;
			}
			else if(DS1302_Time[2] > 28)
					DS1302_Time[2] = 1;
				
		}
		
		if(DS1302_Time[3] > 23){	DS1302_Time[3] = 0;	};
		if(DS1302_Time[4] > 59){	DS1302_Time[4] = 0;	};
		if(DS1302_Time[5] > 59){	DS1302_Time[5] = 0;	};
	}
	if(KeyNum==4)
	{
		--( DS1302_Time[TimeSetSelect] );
		
		if(DS1302_Time[0] < 0){	DS1302_Time[0] = 99;	};
		if(DS1302_Time[1] < 1){	DS1302_Time[1] = 12;	};
		
		if(DS1302_Time[1]==1 || DS1302_Time[1]==3 || 
			DS1302_Time[1]==5 || DS1302_Time[1]==7 || DS1302_Time[1]==8 || 
			DS1302_Time[1]==10 ||	DS1302_Time[1]==12)
		{
			if(DS1302_Time[2] < 1)
				DS1302_Time[2] = 31;
			if(DS1302_Time[2] > 31)
				DS1302_Time[2] = 1;
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || 
			DS1302_Time[1]==9 || DS1302_Time[1]==11)
		{
			if(DS1302_Time[2] < 1)
				DS1302_Time[2] = 30;
			if(DS1302_Time[2] > 30)
				DS1302_Time[2] = 1;
		}
		else
		{
			if(DS1302_Time[0] % 4 == 0)
			{
				if(DS1302_Time[2] < 1)
					DS1302_Time[2] = 29;
				if(DS1302_Time[2] > 29)
					DS1302_Time[2] = 1;
			}
			else if(DS1302_Time[2] < 1)
					DS1302_Time[2] = 28;
			else if(DS1302_Time[2] > 28)
					DS1302_Time[2] = 1;
		}
		
		if(DS1302_Time[3] < 0){	DS1302_Time[3] = 23;	};
		if(DS1302_Time[4] < 0){	DS1302_Time[4] = 59;	};
		if(DS1302_Time[5] < 0){	DS1302_Time[5] = 59;	};
	}
	
	if(TimeSetSelect==0 && TimeSetFlashFlag){LCD_ShowString(1,1,"  ");}
	else{LCD_ShowNum(1,1,DS1302_Time[0],2);}
	if(TimeSetSelect==1 && TimeSetFlashFlag){LCD_ShowString(1,4,"  ");}
	else{LCD_ShowNum(1,4,DS1302_Time[1],2);}
	if(TimeSetSelect==2 && TimeSetFlashFlag){LCD_ShowString(1,7,"  ");}
	else{LCD_ShowNum(1,7,DS1302_Time[2],2);}
	if(TimeSetSelect==3 && TimeSetFlashFlag){LCD_ShowString(2,1,"  ");}
	else{LCD_ShowNum(2,1,DS1302_Time[3],2);}
	if(TimeSetSelect==4 && TimeSetFlashFlag){LCD_ShowString(2,4,"  ");}
	else{LCD_ShowNum(2,4,DS1302_Time[4],2);}
	if(TimeSetSelect==5 && TimeSetFlashFlag){LCD_ShowString(2,7,"  ");}
	else{LCD_ShowNum(2,7,DS1302_Time[5],2);}
	
	if(LastTimeSetSelect != TimeSetSelect)
	{
		LastTimeSetSelect = TimeSetSelect;
		LCD_ShowString(2,10,"      ");
		switch(TimeSetSelect)
		{
			case 0:
				LCD_ShowString(2,10,"year");
				break;
			case 1:
				LCD_ShowString(2,10,"month");
				break;
			case 2:
				LCD_ShowString(2,10,"day");
				break;
			case 3:
				LCD_ShowString(2,10,"hour");
				break;
			case 4:
				LCD_ShowString(2,10,"minute");
				break;
			case 5:
				LCD_ShowString(2,10,"second");
				break;
		}
	}
	
	
}

void main()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	
	DS1302_SetTime();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	while(1)
	{
		KeyNum = Key();
		if(KeyNum==1)
		{
			if(MODE==0)
			{
				MODE=1;
			}
			else if(MODE==1)
			{
				DS1302_SetTime();
				LCD_ShowString(2,10,"      ");
				LastTimeSetSelect = -1;
				MODE=0;
			}
		}
		
		switch(MODE)
		{
			case 0:
				TimeShow();
				break;
			case 1:
				TimeSet();
				break;
		}
	}
}

/**
  *@brief		时间中断函数，用于被修改数据的闪烁
  *@param		无
  *@retval	无
  **/
void Timer0_Routine(void) interrupt 1
{
	static unsigned char T0Count=0;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	++T0Count;
	
	if(T0Count%500==0)
	{
		T0Count=0;
		TimeSetFlashFlag = !TimeSetFlashFlag;
	}
	
}


