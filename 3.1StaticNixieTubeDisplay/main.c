#include <REGX52.H>

unsigned char NixieTable[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	//	ÊýÂë¹Ü¶ÎÂë±í

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
}

void main()
{
	Nixie(2,3);
	while(1)
	{
		
	}
}