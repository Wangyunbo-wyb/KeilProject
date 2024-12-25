#ifndef __CRC_H__
#define __CRC_H__

#include "main.h"

FL_ErrorStatus CRC7_MMC_Cal(void);
FL_ErrorStatus CRC8_Cal(void);
FL_ErrorStatus CRC16_CCITT_Cal(void);
FL_ErrorStatus CRC32_Cal(void);
FL_ErrorStatus CRC16_CCITT_WORD_Cal(void);
FL_ErrorStatus CRC16_CCITT_DMA_Cal(void);
FL_ErrorStatus CRC16_CCITT_WORD_DMA_Cal(void);

#endif
