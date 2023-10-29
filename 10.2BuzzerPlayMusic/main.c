#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

sbit Buzzer = P2^5;

#define P 	0	
#define L1 	1
#define L1_ 2
#define L2 	3
#define L2_ 4
#define L3 	5
#define L4 	6
#define L4_ 7
#define L5 	8
#define L5_ 9
#define L6 	10
#define L6_ 11
#define L7 	12
#define M1 	13
#define M1_ 14
#define M2 	15
#define M2_ 16
#define M3 	17
#define M4 	18
#define M4_ 19
#define M5 	20
#define M5_ 21
#define M6 	22
#define M6_ 23
#define M7 	24
#define H1 	25
#define H1_ 26
#define H2 	27
#define H2_ 28
#define H3 	29
#define H4 	30
#define H4_ 31
#define H5 	32
#define H5_ 33
#define H6 	34
#define H6_ 35
#define H7 	36

//	第0位为休止符
unsigned int FreqTable[] = {0,
	63777,63872,63969,64054,64140,64216,64291,64360,64426,64489,64547,64607,
	64655,64704,64751,64795,64837,64876,64913,64948,64981,65012,65042,65070,
	65095,65120,65144,65166,65186,65206,65225,65242,65259,65274,65289,65303
};

//	4分音符的基准
#define SPEED 500

// 16分音符为基准，	16	-	1，8	-	2，	4	-	4，	2	-	8，	1	-	16
//	//	小星星
//unsigned char code Music[] = {
//	13,4,
//	13,4,
//	20,4,
//	20,4,
//	22,4,
//	22,4,
//	20,8,
//	18,4,
//	18,4,
//	17,4,
//	17,4,
//	15,4,
//	15,4,
//	13,8,
//	
//	0xff
//};

//	//	天空之城
//unsigned char code Music[] = {
//	P,4,
//	P,4,
//	P,4,
//	M6,2,
//	M7,2,
//	H1,6,
//	M7,2,
//	H1,4,
//	H3,4,
//	M7,12,
//	M3,2,
//	M3,2,
//	M6,6,
//	M5,2,
//	M6,4,
//	H1,4,
//	M5,12,
//	M3,4,
//	M4,6,
//	M3,2,
//	M4,4,
//	H1,4,
//	M3,8,
//	P,2,
//	H1,2,
//	H1,2,
//	H1,2,
//	M7,6,
//	M4_,2,
//	M4,4,
//	M7,4,
//	M7,8,
//	P,4,
//	M6,2,
//	M7,2,
//	H1,6,
//	M7,2,
//	H1,4,
//	H3,4,
//	M7,12,
//	M3,2,
//	M3,2,
//	M6,6,
//	M5,2,
//	M6,4,
//	H1,4,
//	M5,12,
//	M2,2,
//	M3,2,
//	M4,4,
//	H1,2,
//	M7,2,
//	M7,2,
//	H1,2,
//	H1,4,
//	H2,2,
//	H2,2,
//	H3,2,
//	H1,2,
//	H1,8,
//	H1,2,
//	M7,2,
//	M6,2,
//	M6,2,
//	M7,4,
//	M5_,4,
//	M6,12,
//	H1,2,
//	H2,2,
//	H3,6,
//	H2,2,
//	H3,4,
//	H5,4,
//	H2,12,
//	M5,2,
//	M5,2,
//	H1,6,
//	M7,2,
//	H1,4,
//	H3,4,
//	H3,16,
//	M6,2,
//	M7,2,
//	H1,4,
//	M7,4,
//	H2,2,
//	H2,2,
//	H1,6,
//	M5,2,
//	M5,8,
//	H4,4,
//	H3,4,
//	H2,4,
//	H1,4,
//	H3,12,
//	H3,4,
//	H6,8,
//	H5,4,
//	H5,4,
//	H3,2,
//	H2,2,
//	H1,8,
//	P,2,
//	H1,2,
//	H2,4,
//	H1,2,
//	H2,2,
//	H2,4,
//	H5,4,
//	H3,12,
//	H3,4,
//	H6,8,
//	H6,8,
//	H3,2,
//	H2,2,
//	H1,8,
//	P,2,
//	H1,2,
//	H2,4,
//	H1,2,
//	M2,2,
//	M2,4,
//	M7,4,
//	H6,4,
//	P,8,
//	M6,2,
//	M7,2,
//	
//	
//	0xff
//};

//	//	东方红
unsigned char code Music[] = {
	M5,4,
	M5,2,
	M6,2,
	M2,8,
	M1,4,
	M1,2,
	L6,2,
	M2,8,
	M5,4,
	M5,4,
	M6,2,
	H1,2,
	M6,2,
	M5,2,
	M1,4,
	M1,2,
	L6,2,
	M2,8,
	M5,4,
	M2,4,
	M1,4,
	L7,2,
	L6,2,
	L5,4,
	M5,4,
	M2,4,
	M3,2,
	M2,2,
	M1,4,
	M1,2,
	L6,2,
	M2,2,
	M3,2,
	M2,2,
	M1,2,
	M2,2,
	M1,2,
	L7,2,
	L6,2,
	L5,8,
	L5,4,
	P,
	
	0xff
};
unsigned char CToF(unsigned char C)
{
	switch(C)
	{
		case L1:
			return L4;
		case M1:
			return M4;
		case H1:
			return H4;
		case L2:
			return L5;
		case M2:
			return M5;
		case H2:
			return H5;
		case L3:
			return L5_;
		case M3:
			return M5_;
		case H3:
			return H5_;
		case L4:
			return L7;
		case M4:
			return M7;
		case H4:
			return H7;
		case L5:
			return L1;
		case M5:
			return M1;
		case H5:
			return H1;
		case L6:
			return L2;
		case M6:
			return M2;
		case H6:
			return H2;
		case L7:
			return L3;
		case M7:
			return M3;
		case H7:
			return H3;
		default:
			return P;
	}
}

unsigned char FreqSelect=0,MusicSelect=0;

void main()
{
	
	
	Timer0_Init();
	while(1)
	{
		if(Music[MusicSelect] == 0xff)
		{
			MusicSelect = 0;
			FreqSelect = 0;
			TR0 = 0;
			Delay(2000);
			TR0=1;
		}
		//FreqSelect=CToF(Music[MusicSelect]);
		FreqSelect = Music[MusicSelect];
		++MusicSelect;
		Delay(SPEED/4*Music[MusicSelect]);
		++MusicSelect;
		TR0=0;
		Delay(5);
		TR0=1;
		
		
	}
}

void Timer0_Routine(void) interrupt 1
{
	if(FreqTable[FreqSelect])	//	如果不是休止符就震动蜂鸣器
	{
		TL0 = FreqTable[FreqSelect]%256;				//设置定时初始值
		TH0 = FreqTable[FreqSelect]/256;				//设置定时初始值
		Buzzer = !Buzzer;
	}
}	
