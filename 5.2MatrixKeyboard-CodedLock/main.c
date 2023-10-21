#include <REGX52.H>
#include <string.h>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char KeyNum;
unsigned char inputPWD[17] = {0};	//	存放输入密码的字符串，初始全为'*'
unsigned char rightPWD[17] = "7355608";	//	正确的密码

void main()
{
	int n = 0;	//	当前密码位数
	
	LCD_Init();
	LCD_ShowString(1,1,"Password:>");
	LCD_ShowString(2,1,"****************");	//	输出全空密码
	while(1)
	{
		int i = 0;	//	循环计数变量
		
		KeyNum = MatrixKey();
		if(KeyNum)	//	如果键码标识为0表示没按下任何按键
		{
			if(KeyNum<=10)	//	如果s1~s10被按下，输入密码
			{
				if(n<16)
				{
					inputPWD[n] = KeyNum%10+48;	//	0-9	，其中键码为1-9时也显示1-9，键码为10时显示0
					++n;
				}
				else
				{
					LCD_ShowString(2,1,"Excessive input!");
					Delay(2000);
				}
				
				for(i=1;i<=(16-n);++i)
					LCD_ShowChar(2,i,'*');	//	填充'*'循环
				
				LCD_ShowString(2,i,inputPWD);	//	输出密码
			}
			else if(KeyNum==11)	//	s11按下后表示确认密码
			{
				if(0==strcmp(inputPWD,rightPWD))
				{
					LCD_ShowString(1,12,"Right");	//	输出成功信息
					}
				}
				else
				{
					LCD_ShowString(1,12,"Wrong");	//	输出失败信息
				}
				Delay(2000);
				LCD_ShowString(1,12,"     ");	//	清空正确与错误结果显示
				n=0;	//	确认后无论输入正确与否，清空密码
				memset(inputPWD,0,16);
				LCD_ShowString(2,1,"****************");	//	输出全空密码
			}
			else if(KeyNum==12)	//	s12按下后表示清空输入的密码
			{
				n=0;	//	确认后无论输入正确与否，清空密码
				memset(inputPWD,0,16);
				LCD_ShowString(2,1,"****************");	//	输出全空密码
			}

		}
	}
}