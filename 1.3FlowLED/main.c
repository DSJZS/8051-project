#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms(unsigned int xms)	//@11.0592MHz
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
	int i = 0;
	while(1)
	{
		P2 = ~(0x1<<i);
		Delay1ms(300);
		++i;
		if(i==8)
			i=0;
	}
}