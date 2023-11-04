#include <Nixie.h>

//	数码管段码表								0			1			2			3			4			5			6			7			8			9			无		-
unsigned char NixieTable[] = {	0x3f,	0x06,	0x5b,	0x4f,	0x66,	0x6d,	0x7d,	0x07,	0x7f,	0x6f,	0x00,	0x40};

//	数码管缓冲区，用于表示每位数码管的显示，缓冲区第一位空置
unsigned char Nixie_Buf[9]={0,10,10,10,10,10,10,10,10};

//void Nixie(unsigned char Location,unsigned char Number)
//{
//	switch(Location)
//	{
//		case 1:	P2_4 = 1;	P2_3 = 1;	P2_2 = 1;	break;
//		case 2:	P2_4 = 1;	P2_3 = 1;	P2_2 = 0;	break;
//		case 3:	P2_4 = 1;	P2_3 = 0;	P2_2 = 1;	break;
//		case 4:	P2_4 = 1;	P2_3 = 0;	P2_2 = 0;	break;
//		case 5:	P2_4 = 0;	P2_3 = 1;	P2_2 = 1;	break;
//		case 6:	P2_4 = 0;	P2_3 = 1;	P2_2 = 0;	break;
//		case 7:	P2_4 = 0;	P2_3 = 0;	P2_2 = 1;	break;
//		case 8:	P2_4 = 0;	P2_3 = 0;	P2_2 = 0;	break;
//		default:	break;
//	}
//	P0 = NixieTable[Number];
//	Delay(1);
//	P0 = 0x00;
//}

/**
  *@brief		设置数码管的缓冲区
  *@param		Location	位选，即那一位数码管的缓冲区要被修改
	*@param		Number		段选，即数码管的缓冲区要被修改为显示什么
  *@retval	无
  **/
void Nixie_SetBuf(unsigned char Location,unsigned char Number)
{
	Nixie_Buf[Location] = Number;
}

/**
  *@brief		扫描数码管
  *@param		Location	位选，即那一位数码管显示
	*@param		Number		段选，即数码管显示什么
  *@retval	无
  **/
void Nixie_Scan(unsigned char Location,unsigned char Number)
{
	P0 = 0x00;
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

/**
	*@brief		用于在定时器中断函数中扫描各个数码管，推荐以2ms为周期执行
  *@param		无
  *@retval	无
  **/
void Nixie_Loop(void)
{
	static unsigned char i = 1;
	Nixie_Scan(i,Nixie_Buf[i]);
	++i;
	if(i>8)
		i=1;
}