#include <REGX52.H>
#include "Nixie.h"
#include "Motor.h"
#include "IR.h"


unsigned char Command=0,Speed=0;

void main()
{
	Motor_Init();
	IR_Init();
	
	while(1)
	{	
		if( IR_GetDataFlag())
		{
			Command = IR_GetCommand();
				
			if(Command == IR_0){	Speed=0;	Motor_SetSpeed(0);}
			if(Command == IR_1){	Speed=1;	Motor_SetSpeed(50);}
			if(Command == IR_2){	Speed=2;	Motor_SetSpeed(75);}
			if(Command == IR_3){	Speed=3;	Motor_SetSpeed(100);}
		}

		Nixie(1,Speed);
	}
}

