#include <REGX52.H>
#include "Timer0.h"
#include "LCD1602.h"
#include "Delay.h"

unsigned char sec,min,hour,day;

unsigned char Count;

void main()
{
	int i = 0;
	
	LCD_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"Clock:D  H  M  S");
	LCD_ShowString(2,1,"       :  :  :  ");
	
	while(1)
	{
		if(Count==0)
			LCD_ShowString(2,1,"     ");
		else
			LCD_ShowChar(2,Count,'*');
		LCD_ShowNum(2,15,sec,2);
		LCD_ShowNum(2,12,min,2);
		LCD_ShowNum(2,9,hour,2);
		LCD_ShowNum(2,6,hour,2);
	}
}

void Timer0_Routine(void) interrupt 1
{
	static unsigned int T0count;
	
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	++T0count;
	
	if(T0count % 1000 == 0)
	{
		T0count = 0;
		++sec;
		++Count;
		if(Count==5)
			Count=0;
		if(sec==60)
		{
			sec=0;
			++min;
			if(min==60)
			{
				min=0;
				++hour;
				if(hour>=24)
				{
					hour=0;
					++day;
				}
			}
		}
	}
}