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

unsigned char LEDNum;

void main()
{
	P2 = 0xff;
	while(1)
	{
		if(P3_1 == 0)
		{
			Delay(20);
			while(P3_1 == 0);
			Delay(20);
			
			LEDNum++;
			if(LEDNum >= 8)
				LEDNum = 0;
			P2 = ~(0x01<<LEDNum);
		}
	}
}