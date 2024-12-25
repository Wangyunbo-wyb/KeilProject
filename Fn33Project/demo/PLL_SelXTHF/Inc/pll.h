#ifndef __PLL_H__
#define __PLL_H__

#include "main.h"
#ifndef MFANG
    #include <stdio.h>
#endif

extern uint32_t SYSCLKSELErrorState;

void FDET_IRQHandler(void);
void CMU_PLL_ConfigDomain_SYSTEM(uint32_t Source, uint32_t PLL_REFPSC, uint32_t PLL_DB, uint32_t PLL_OSEL);

void SelRCHFToPLL(uint32_t rchf, uint32_t clock);
void SelXTHFToPLL(uint32_t div, uint32_t clock);

void RCHFInit(uint32_t clock);
void XTHFInit(void);
#endif
