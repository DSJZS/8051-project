#ifndef __TETRIS_H__
#define __TETRIS_H__

void Tetris_Init(void);
void Tetris_Display(void);
unsigned char Tetris_Fall(void);
void  Tetris_ToLeft(void);
void  Tetris_ToRight(void);
void Tetris_Stack(void);
void Tetris_Create(void);
void Tetris_Full(void);
void Tetris_RtLeft(void);
void Tetris_RtRight(void);
unsigned char Tetris_GameOver(void);

#endif