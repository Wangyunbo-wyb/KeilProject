#ifndef __U7816_H__
#define __U7816_H__
#include "main.h"

void Delay_Netu(unsigned char Num);
uint8_t Judge_Edge(void);
uint8_t Get_7816_Char(unsigned char *Data);
uint8_t Snd_7816_Byte(unsigned char Data);
uint8_t ColdReset(void);
extern uint8_t U7816Transfer(void);

#endif
