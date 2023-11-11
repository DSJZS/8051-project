#ifndef __MSG_H__
#define __MSG_H__

//	消息结构体，用于存储每一个消息
typedef struct TagMSG{
	unsigned char message;	//	消息
	unsigned char param;		//	消息参数
	unsigned char count;		//	消息重复计数，每个新消息为1
}MSG;

//	消息枚举
enum CyanMessage{
	CM_Init = 0,		//	初始化
	CM_INDBTN_DOWN,	//	独立按键按下
	CM_INDBTN_UP,		//	独立按键松开
	CM_MATKEY_DOWN,	//	矩阵键盘按下
	CM_MATKEY_UP		//	矩阵键盘松开
};
//	虚拟键码
enum Virtualkey
{
	VK_INDBTN1=1,
	VK_INDBTN2,
	VK_INDBTN3,
	VK_INDBTN4,
};

//	取出1字节数据的高4位与低4位
#define HIGCHAR(c) (((c)>>4)&0x0f)
#define LOWCHAR(c) ((c)&0x0f)

void MSG_InitQueue(void);
unsigned char MSG_SendMessage(MSG* M);
unsigned char MSG_GetMessage(MSG* M);
void MSG_PostMessage(MSG* M);

#endif