#ifndef __DEMO_RTC_H__
#define __DEMO_RTC_H__

#include "fm33lg0xx_fl.h"

uint8_t RTCB_GetRTCB(FL_RTCB_InitTypeDef *InitStructer);
uint8_t RTCB_SetRTCB(FL_RTCB_InitTypeDef *InitStructer);
void RTCB_Clk_XTLF_Enable(void);
void RTCB_ReadWrite(void);
void RTCB_AlarmTimeSet(void);
void RTCB_TimeMarkOut(void);
void RTCB_Stamp(void);
void RTCB_Clear_Buckup_REG(void);
void RTCB_Init(void);
#endif
