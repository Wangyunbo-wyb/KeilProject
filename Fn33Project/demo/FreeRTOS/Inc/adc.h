#ifndef __ADC_H__
#define __ADC_H__

#include "main.h"

extern uint32_t GetSingleChannelVoltage_POLL(uint32_t channel);
extern void ADC_Init(void);
#endif
