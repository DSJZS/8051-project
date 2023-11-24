#include "Tetris.h"
#include "MatrixLED.h"

/*俄罗斯方块游戏
思路：
通过13个int类型的变量充当容器存放方块

51单片机中int为2byte大小，有16bit，左右两边的四个bit充当边界，便于后续位操作判断
中间的八个bit用于存放方块的数据

第0-3个int变量是方块的刷新的区域，因为俄罗斯方块里的方块图形最多占4行，
而且都是一行一行的从顶部刷新出来，创建的刷新的区域有利于实现这一点

第4-11个int变量是显示区域，LED点阵屏有8行8列，正好全部表示

第12-13个int变量是容器底部，用于后续的逻辑判断，
底部设置为两行而不是一行是为了应对后续可能存在的越界问题
*/

//	方块容器，存放堆积的、下降的方块
int ball[13] = {0};
//	初始化时如下图，1代表边界
//	1111000000001111	*	0-3		方块刷新区域
//	1111000000001111	*
//	1111000000001111	*
//	1111000000001111	*
//	1111000000001111	-	4-11	显示区域
//	1111000000001111	-
//	1111000000001111	-
//	1111000000001111	-
//	1111000000001111	-
//	1111000000001111	-
//	1111000000001111	-
//	1111000000001111	-
//	1111111111111111	+	12-13	容器底部
//	1111111111111111	+	

//	存放下降的方块
int fall[4] = {0};
//	初始化时如下图
//	00000000	-	存储正在下降的方块
//	00000000	-
//	00000000	-
//	00000000	-

//	每个方块的每一个旋转图形
int code Data[7][4][4] = {
	//	@
	// @@@
	0x00,0x02,0x07,0x00,0x00,0x02,0x03,0x02,0x00,0x07,0x02,0x00,0x00,0x02,0x06,0x02,
	//	@@
	//	 @
	//	 @
	0x00,0x06,0x02,0x02,0x00,0x01,0x07,0x00,0x00,0x02,0x02,0x03,0x00,0x07,0x04,0x00,
	//	@@
	//	@
	//	@
	0x00,0x03,0x02,0x02,0x00,0x07,0x01,0x00,0x00,0x01,0x01,0x03,0x00,0x07,0x01,0x00,
	// @@
	//	@@
	0x00,0x06,0x03,0x00,0x00,0x01,0x03,0x02,0x00,0x06,0x03,0x00,0x00,0x01,0x03,0x02,
	// 	@@
	// @@
	0x00,0x03,0x06,0x00,0x00,0x02,0x03,0x01,0x00,0x03,0x06,0x00,0x00,0x02,0x03,0x01,
	// 	@@
	// 	@@
	0x00,0x03,0x03,0x00,0x00,0x03,0x03,0x00,0x00,0x03,0x03,0x00,0x00,0x03,0x03,0x00,
	// 	@@@@
	0x00,0x00,0x0f,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x0f,0x00,0x01,0x01,0x01,0x01
};

enum Shape{	//	方块类型枚举
	//	@
	// @@@
	Shape_T = 0,
	//	@@
	//	 @
	//	 @
	Shape_L,
	//	@@
	//	@
	//	@
	Shape_J,
	// @@
	//	@@
	Shape_Z,
	// 	@@
	// @@
	Shape_S,
	// 	@@
	// 	@@
	Shape_O,
	// 	@@@@
	Shape_I
};

char bottom = 0;	//	4-12	方块最底部在容器的哪一行
char LShift = 0;	//	2-		方块最右边相较于容器最右边(bit0)左移多少位
char shape = 0;		//	0-6		当前方块的形状
char status = 0;	//	0-3		当前方块的旋转状态

/**
  *@brief		创建一个方块图形
  *@param		无
  *@retval		无
  **/
void Tetris_Create(void)
{
	char i = 0;
	LShift = 6;
	status = 0;
	bottom = 3;
	++shape;
	if(shape > Shape_I)
		shape = Shape_T;
	for(i=0;i<4;++i)
	{
		fall[i] = Data[shape][status][i];
	}
}

/**
  *@brief		初始化游戏
  *@param		无
  *@retval		无
  **/
void Tetris_Init(void)
{
	char i = 0;
	for(i=0;i<12;++i)
	{
		ball[i] = 0xF00F;
	}
	ball[12] = 0xFFFF;
	ball[13] = 0xFFFF;
	shape = -1;
	Tetris_Create();
}

/**
  *@brief		显示容器内的方块和正在下降的方块
  *@param		无
  *@retval		无
  **/
void Tetris_Display(void)
{
	char i = 0;
	for(i=11;i>=4;--i)
	{
		if(i<=bottom && i>=(bottom-3))
			MatrixLED_ShowRow(i-4,( ball[i] | (fall[3 - (bottom-i)]<<LShift) ) >> 4 );
		else
			MatrixLED_ShowRow(i-4,ball[i] >> 4);
	}
}

/**
  *@brief		使方块下降
  *@param		无
*@retval		下降成功为 1 ，否则为 0
  **/
unsigned char Tetris_Fall(void)
{
	char i = 0;
	for(i=3;i>=0;--i)
	{
		if(( (fall[i]<<LShift) & ball[bottom - (3-i) + 1] ) != 0 )
		{
			return 0;
		}
	}
	++bottom;
	return 1;
}

/**
  *@brief		使方块朝左移动
  *@param		无
  *@retval		无
  **/
void Tetris_ToLeft(void)
{
	char i = 0;
	for(i=3;i>=0;--i)
	{
		if(( ( (fall[i]<<LShift) <<1) & ball[bottom - (3-i)] ) != 0 )
		{
			return;
		}
	}
	++LShift;
}

/**
  *@brief		使方块朝右移动
  *@param		无
  *@retval		无
  **/
void Tetris_ToRight(void)
{
	char i = 0;
	for(i=3;i>=0;--i)
	{
		if(( ( (fall[i]<<LShift) >>1) & ball[bottom - (3-i)] ) != 0 )
		{
			return;
		}
	}
	--LShift;
}

/**
  *@brief		将不再下降的方块堆叠到容器中
  *@param		无
  *@retval		无
  **/
void Tetris_Stack(void)
{
	char i = 0;
	for(i=3;i>=0;--i)
	{
		ball[bottom - (3-i)] |= (fall[i]<<LShift) ;
	}
}

/**
  *@brief		判断并且消除容器中满一行的方块
  *@param		无
  *@retval		无
  **/
void Tetris_Full(void)
{
	char i = 0;
	for(i=11;i>=4;--i)
	{
		if(ball[i] == 0xFFFF)
		{
			char j = 0;
			for(j=i;j>=5;--j)
			{
				ball[j] = ball[j-1];
			}
		}
	}
}

/**
  *@brief		使方块朝左旋转
  *@param		无
  *@retval		无
  **/
void Tetris_RtLeft(void)
{
	char i = 0;
	char tmp = status;
	--tmp;
	if(tmp < 0)
		tmp = 3;
	
	for(i=3;i>=0;--i)
	{
		if(( ( (Data[shape][tmp][i]<<LShift) ) & ball[bottom - (3-i)] ) != 0 )
		{
			return;
		}
	}
	status = tmp;
	for(i=0;i<4;++i)
	{
		fall[i] = Data[shape][status][i];
	}
}

/**
  *@brief		使方块朝右旋转
  *@param		无
  *@retval		无
  **/
void Tetris_RtRight(void)
{
	char i = 0;
	char tmp = status;
	++tmp;
	if(tmp > 3)
		tmp = 0;
	
	for(i=3;i>=0;--i)
	{
		if(( ( (Data[shape][tmp][i]<<LShift) ) & ball[bottom - (3-i)] ) != 0 )
		{
			return;
		}
	}
	status = tmp;
	for(i=0;i<4;++i)
	{
		fall[i] = Data[shape][status][i];
	}
}

/**
  *@brief		判断游戏是否结束
  *@param		无
  *@retval		无
  **/
unsigned char Tetris_GameOver(void)
{
	char i = 0;
	for(i=0;i<4;++i)
	{
		if(ball[i] != 0xF00F)
			return 1;
	}
	return 0;
}
