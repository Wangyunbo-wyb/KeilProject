#ifndef __ADC_H__
#define __ADC_H__

#include "fm33lg0xx_fl.h"

extern void ADC_Config(void);
extern void ADC_IRQHandler(void);
extern uint32_t GetSingleChannelVoltage_IT(void);
extern volatile uint8_t ADCComplete;

#endif
