#include <REGX52.H>

#include "LCD1602.h"
#include "Delay.h"

int result = 0;

void main()
{
	LCD_Init();
	
	while(1)
	{
		LCD_ShowNum(1,1,result++,16);
		Delay(result);
	}
}