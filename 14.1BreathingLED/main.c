#include <REGX52.H>

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time = 0,i = 0;
	while(1)
	{
		for(Time=0;Time<100;++Time)
		{
			for(i=0;i<20;++i)
			{
				P2 |= 0xff;
				P2 &= 0xfc;
				Delay(Time);
				P2 |= 0xff;
				P2 &= 0xf3;
				Delay(100-Time);
			}
		}
		for(Time=100;Time>0;--Time)
		{
			for(i=0;i<20;++i)
			{
				P2 |= 0xff;
				P2 &= 0xfc;
				Delay(Time);
				P2 |= 0xff;
				P2 &= 0xf3;
				Delay(100-Time);
			}
		}
	}
}