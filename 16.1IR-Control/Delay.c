#include "Delay.h"

void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms--)
	{
		_nop_();
		i = 2;
		j = 237;
		do
		{
			while (--j);
		} while (--i);
	}
}