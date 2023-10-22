#include <REGX52.H>
#include <INTRINS.H>
#include "Timer0.h"
#include "Key.h"

unsigned char KeyNum=0;	//	键码
unsigned char LEDMode=0;	//	流水灯模式

//	主函数
void main()
{
	P2 = 0xfe;
	Timer0_Init();
	while(1)
	{
		KeyNum = Key();
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				++LEDMode;
				LEDMode %= 2;
			}
		}
	}
}


//	中断服务函数
void Timer0_Routine(void) interrupt 1
{	
	static unsigned int T0Count = 0;
	
//	TH0 = 64536/256;	//	为计时器赋初值，达到计时1ms的效果
//	TL0 = 64536%256;
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	
	++T0Count;
	if(T0Count%500==0)
	{
		T0Count=0;
		if(LEDMode == 0)
			P2 = _crol_(P2,1);
		if(LEDMode == 1)
			P2 = _cror_(P2,1);
	}
}