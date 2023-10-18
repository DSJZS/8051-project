#include <REGX52.H>
#include <INTRINS.H>

void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}

}


void main()
{
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(20);	//	过滤按下按键时的抖动
			while(P3_1 == 0);	//	等待按键松开
			Delay(20);	//	过滤松开按键时的抖动
			P2_0 = ~P2_0;
		}
		
	}
}