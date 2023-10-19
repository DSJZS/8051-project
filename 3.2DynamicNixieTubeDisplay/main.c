#include <REGX52.H>
#include <INTRINS.H>

unsigned char NixieTable[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	//	数码管段码表

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



void Nixie(unsigned char Location,unsigned char Number)
{
	switch(Location)
	{
		case 1:	P2_4 = 1;	P2_3 = 1;	P2_2 = 1;	break;
		case 2:	P2_4 = 1;	P2_3 = 1;	P2_2 = 0;	break;
		case 3:	P2_4 = 1;	P2_3 = 0;	P2_2 = 1;	break;
		case 4:	P2_4 = 1;	P2_3 = 0;	P2_2 = 0;	break;
		case 5:	P2_4 = 0;	P2_3 = 1;	P2_2 = 1;	break;
		case 6:	P2_4 = 0;	P2_3 = 1;	P2_2 = 0;	break;
		case 7:	P2_4 = 0;	P2_3 = 0;	P2_2 = 1;	break;
		case 8:	P2_4 = 0;	P2_3 = 0;	P2_2 = 0;	break;
		default:	break;
	}
	P0 = NixieTable[Number];
	Delay(1);
	P0 = 0x00;
}

void main()
{
	while(1)
	{
		Nixie(1,2);
		Nixie(2,0);
		Nixie(3,2);
		Nixie(4,3);
		Nixie(5,1);
		Nixie(6,0);
		Nixie(7,1);
		Nixie(8,8);
	}
}