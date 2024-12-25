#ifndef __ADC_H__
#define __ADC_H__

#include "fm33lg0xx_fl.h"

extern uint32_t GetSingleChannelVoltage_DMA(void);
extern void ADC_Config(void);
extern void DMA_IRQHandler(void);
extern void ADC_DMA_Config(uint16_t *buffer, uint32_t length);
extern volatile uint8_t ADCComplete;
extern uint16_t DMAResult[2];
#endif
