#ifndef __ADC_H__
#define __ADC_H__

#include "fm33lg0xx_fl.h"


extern void DAC_EXTTrigger(void);
extern void DMA_IRQHandler(void);
extern void GPIO_IRQHandler(void);
extern volatile uint8_t DACComplete;
#endif
