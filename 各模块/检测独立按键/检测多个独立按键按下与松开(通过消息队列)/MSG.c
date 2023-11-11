#include "MSG.h"

#define QUEUE_CAP 10	//	消息队列最多存多少消息

//	消息队列，为顺序队，用于存放各个信息(考虑改为链队)
static struct MessageQueue{
	int Capacity;	//	队列容量
	int front;	// 用下标代替头指针
	int rear;		// 用下标代替尾指针
	MSG Data[QUEUE_CAP+1];	//	消息队列数据
}MQ;


/**
	*@brief		判断消息队列是否为空
  *@param		无
	*@retval	消息队列为空返回 1，否则返回 0
  **/
static unsigned char MSG_isEmpty()
{
	return (MQ.front == MQ.rear);	//	利用头指针和尾指针的位置判断是否为空
}


/**
  *@brief		消息溢出处理函数
  *@param		msg	-	溢出消息的指针
  *@retval	处理成功返回 1，失败返回 0
  **/
static unsigned char MSG_MQOverflow(MSG* M)
{
	//	当前不处理，因为51单片机基本上不可能溢出
	
	return 0;
}


/**
  *@brief		发出消息到消息队列
  *@param		msg	-	要发送消息的指针
  *@retval	发送成功返回 1，失败返回 0
  **/
unsigned char MSG_SendMessage(MSG* M)
{
	int i = 0;	//	for循环计数变量
	
	//	从消息队列中的最后一个消息往前找是否有重复的消息
	for(i = (MQ.rear+MQ.Capacity-1)%MQ.Capacity;i != (MQ.front+MQ.Capacity-1)%MQ.Capacity;i = (i+MQ.Capacity-1)%MQ.Capacity)
	{
		//	找到重复的消息
		if((MQ.Data[i].message == M->message) && (MQ.Data[i].param == M->param))
		{
			// 如果该信息的重复计数没有满，则加一并且结束函数
			// 如果满了，就退出循环，创建一个新消息，并且重新计数
			if(MQ.Data[i].count <= 255)
			{
				++(MQ.Data[i].count);
				return 1;
			}
			else
			{
				break;
			}
		}
	}
	//	判断消息队列是否已满
	if( (MQ.rear+1) % MQ.Capacity == MQ.front )
	{
		return MSG_MQOverflow(M);	//	如果满了就执行消息队列溢出函数
	}
	else
	{
		MQ.Data[MQ.rear] = *M;	//	将消息放入队列末尾
		++(MQ.Data[MQ.rear].count);	//	使消息重复计数默认为 1
		MQ.rear = (MQ.rear+1) % MQ.Capacity;	//	尾指针往后移动
		return 1;
	}
}


/**
  *@brief		接收消息队列对头消息
  *@param		msg	-	存放接收信息的结构体指针
  *@retval	有消息接收返回 1，没有则返回 0
  **/
unsigned char MSG_GetMessage(MSG* M)
{
	if(MSG_isEmpty())	//	判断消息队列是否为空
		return 0;
	*M = MQ.Data[MQ.front];	//	将队首的消息读出
	MQ.front = (MQ.front+1) % MQ.Capacity;	//	使头指针往后移动
	return 1;
}


//	告知程序外部有MessageProc()函数
extern void MessageProc(unsigned char message,unsigned char param,unsigned char count);
/**
  *@brief		发布消息给消息处理函数(该函数需要自行编写)
  *@param		msg	-	存放要发布信息的结构体指针
  *@retval	无
  **/
void MSG_PostMessage(MSG* M)
{
	//	将数据发送到消息处理函数
	MessageProc(M->message,M->param,M->count);
}

/**
  *@brief		发送消息队列初始化消息
  *@param		无
  *@retval	无
  **/
static void MSG_SendInitMessage(void)
{
	MSG msg = {	CM_Init,	0	,	1};
	MQ.Data[MQ.rear] = msg;								//	将消息放入队列末尾
	MQ.rear = (MQ.rear+1) % MQ.Capacity;	//	尾指针往后移动
}
/**
  *@brief		初始化消息队列
  *@param		无
  *@retval	无
  **/
void MSG_InitQueue(void)
{
	MQ.Capacity = QUEUE_CAP;	//	设置容量大小
	MQ.front = 0;	//	置零头指针	
	MQ.rear = 0;	//	置零尾指针
	MSG_SendInitMessage();	//	发送初始化消息
}