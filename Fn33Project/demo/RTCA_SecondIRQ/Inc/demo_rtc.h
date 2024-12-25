#ifndef __DEMO_RTC_H__
#define __DEMO_RTC_H__

#include "fm33lg0xx_fl.h"

uint8_t RTCA_GetRTCA(FL_RTCA_InitTypeDef *InitStructer);
uint8_t RTCA_SetRTCA(FL_RTCA_InitTypeDef *InitStructer);
void RTCA_ReadWrite(void);
void RTCA_AlarmTimeSet(void);
void RTCA_TimeMarkOut(void);
void RTCA_Init(void);

#endif
