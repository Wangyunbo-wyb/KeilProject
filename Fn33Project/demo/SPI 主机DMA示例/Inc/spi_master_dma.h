#ifndef __SPI_MASTER_DMARW_H__
#define __SPI_MASTER_DMARW_H__

#include "fm33lg0xx_fl.h"

void DMA_IRQHandler(void);
void SPI_DMARW_Setup(void);
void SPI_DMARW_Loop(void);

#endif
