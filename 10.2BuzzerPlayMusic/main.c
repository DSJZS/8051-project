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
// 16分音符为基准，	16	-	1，8	-	2，	4	-	4，	2	-	8，	1	-	16
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
//	M4_,4,
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
// 16分音符为基准，	16	-	1，8	-	2，	4	-	4，	2	-	8，	1	-	16
//unsigned char code Music[] = {
//	M5,4,
//	M5,2,
//	M6,2,
//	M2,8,
//	M1,4,
//	M1,2,
//	L6,2,
//	M2,8,
//	M5,4,
//	M5,4,
//	M6,2,
//	H1,2,
//	M6,2,
//	M5,2,
//	M1,4,
//	M1,2,
//	L6,2,
//	M2,8,
//	M5,4,
//	M2,4,
//	M1,4,
//	L7,2,
//	L6,2,
//	L5,4,
//	M5,4,
//	M2,4,
//	M3,2,
//	M2,2,
//	M1,4,
//	M1,2,
//	L6,2,
//	M2,2,
//	M3,2,
//	M2,2,
//	M1,2,
//	M2,2,
//	M1,2,
//	L7,2,
//	L6,2,
//	L5,8,
//	L5,4,
//	P,
//	
//	0xff
//};

//	//	以恋结缘
// 32分音符为基准，	32	-	1		16	-	2，8	-	4，	4	-	8，	2	-	16，	1	-	32
unsigned char code Music[] = {
	P,4,
	L6,4,
	M1,4,
	M2,4,
	P,4,
	L6,4,
	M1,4,
	M2,4,	//	1-1
	
	P,4,
	L6,4,
	M1,4,
	M2,4,
	M4,4,
	M2,4,
	M1,4,
	L6,4,	//	1-2
	
	L5,7,
	P,1,
	L4,4,
	L5,4,
	L5,16,//	1-3
	
	L5,24,
	L5,6,
	P,2,	//	1-4
	
	P,4,
	L6,4,
	M1,4,
	M2,4,
	P,4,
	L6,4,
	M1,4,
	M2,4,	//	1-5
	
	P,4,
	L6,4,
	M1,4,
	M2,4,
	M4,4,
	M2,4,
	M4,4,
	M6,4,	//
	
	M5,7,
	P,1,
	M1,4,
	M1,4,
	M1,16,	//
	
	M1,16,
	M1,7,
	P,1,
	M1,4,
	M2,4,	//
	
	M3,7,
	P,1,
	M4,4,
	M3,8,
	M4,4,
	M4,3,
	P,1,
	M3,4,	//	
	
	M3,4,
	M2,4,
	M2,3,
	P,1,
	M2,4,
	M2,8,
	M2,3,
	P,1,
	M2,4,	//	
	
	M2,7,	/**/
	P,1,
	M3,4,
	M2,8,
	M3,4,
	M3,3,	/**/
	P,1,
	M2,4,	//
	
	M2,4,
	M1,4,
	M1,3,	/**/
	P,1,
	M1,4,
	M1,7,	/**/
	P,1,
	L6,4,
	L7,4,	//
	
	M1,7,
	P,1,
	M2,4,
	M3,8,
	M4,4,
	M4,7,
	P,1,	//
	
	H1,7,
	P,1,
	M4,7,
	P,1,
	M4,4,
	M2,4,
	M4,4,
	M5,4,	//	
	
	M5,32,	//
	
	M5,24,
	M5,6,
	P,2,	//
	
	M6,7,
	P,1,
	M5,4,
	M4,4,
	M5,7,
	P,1,
	M6,7,
	P,1,	//
	
	M5,4,
	M6,4,
	M5,4,
	M4,4,
	M1,14,
	P,2,	//
	
	M2,7,
	P,1,
	M4,4,
	M2,4,
	M5,4,
	M6,4,
	M5,4,
	M4,4,	//
	
	M5,4,
	M4,4,
	M5,7,
	P,1,
	M6,14,
	P,2,	//
	
	H2,7,
	P,1,
	H1,4,
	H2,4,
	M6,7,
	P,1,
	H1,4,
	M6,4,	//
	
	M5,4,
	M4,4,
	M5,4,
	M6,4,
	M2,7,
	P,1,
	M2,4,
	M3,4,	//
	
	M4,7,
	P,1,
	M5,7,
	P,1,
	M6,7,
	P,1,
	H1,7,
	P,1,	//
	
	M6,24,
	M6,6,
	P,2,	//
	
	P,8,
	P,8,
	P,4,
	M6,4,
	H1,4,
	P,4,	//	5-5
	
	H2,4,
	H2,1,
	P,1,
	H2,2,
	H1,4,
	H2,4,
	M6,14,
	P,2,	//	6-1
	
	P,4,
	H2,4,
	H2,4,
	H1,4,
	H2,4,
	H1,4,
	M6,7,
	P,1,	//	6-2
	
	M5,4,
	M5,1,
	P,1,
	M5,2,
	M6,4,
	H1,4,
	H2,7,
	P,1,
	M6,7,
	P,1,	//	6-3
	
	M5,4,
	M6,4,
	M5,4,
	M4,4,
	M6,14,
	P,2,	//	6-4
	
	M5,4,
	M5,1,
	P,1,
	M5,2,
	M4,4,
	M6,4,
	M2,14,
	P,2,	//	6-5
	
	P,4,
	M5,4,
	M5,4,
	M6,4,
	M5,4,
	M4,4,
	M4,3,
	P,1,
	M5,4,	//	7-1
	
	M6,24,
	M6,6,
	P,2,	//	7-2
	
	M5,8,
	M5,3,
	P,1,
	M4,4,
	P,4,
	M6,4,
	H1,4,
	P,4,	//	7-3
	
	H2,4,
	H2,1,
	P,1,
	H2,2,
	H1,4,
	H2,4,
	M6,14,
	P,2,	//	7-4
	
	P,4,
	H2,4,
	H2,4,
	H1,4,
	H2,4,
	H1,4,
	M6,7,
	P,1,	//	7-5
	
	M5,4,
	M5,1,
	P,1,
	M5,2,
	M6,4,
	H1,4,
	H2,7,
	P,1,
	M6,7,
	P,1,	//	8-1
	
	M5,4,
	M4,4,
	M5,4,
	M6,4,
	M2,14,
	P,2,	//	8-2
	
	M2,7,
	P,1,
	M4,4,
	M2,4,
	M5,7,
	P,1,
	M4,4,
	M5,4,	//	8-3
	
	M6,7,
	P,1,
	M5,4,
	M6,4,
	H1,7,
	P,1,
	H3,7,
	P,1,	//	8-4
	
	H3,24,
	H3,6,
	P,2,	//	8-5
	
	H2,24,
	H2,6,
	P,2,	//	9-1
	
	0xff
};

unsigned int FreqSelect=0,MusicSelect=0;

unsigned char GToC(unsigned char Music)
{
	switch(Music)
	{
		case L1:return L5;
		case L2:return L6;
		case L3:return L7;
		case L4:return M1;
		case L5:return M2;
		case L6:return M3;
		case L7:return M4_;
		case M1:return M5;
		case M2:return M6;
		case M3:return M7;
		case M4:return H1;
		case M5:return H2;
		case M6:return H3;
		case M7:return H4_;
		case H1:return H5;
		case H2:return H6;
		case H3:return H7;
		default:return P;
	}
}

void main()
{
	
	
	Timer0_Init();
	while(1)
	{
		if(Music[MusicSelect] == 0xff)
		{
			while(1);
		}
		
		FreqSelect = GToC(Music[MusicSelect]);
		++MusicSelect;
		Delay(SPEED/8.0f*Music[MusicSelect]);
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
