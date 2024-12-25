#include "clock.h"

void ClockInit(uint32_t clock)
{
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_1CYCLE);
    switch(clock)
    {
        case FL_CMU_RCHF_FREQUENCY_8MHZ:
            FL_CMU_RCHF_WriteTrimValue(RCHF8M_TRIM);
            FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
            FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV1);
            break;

        case FL_CMU_RCHF_FREQUENCY_16MHZ:
            FL_CMU_RCHF_WriteTrimValue(RCHF16M_TRIM);
            FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
            FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV2);
            break;

        case FL_CMU_RCHF_FREQUENCY_24MHZ:
            FL_CMU_RCHF_WriteTrimValue(RCHF24M_TRIM);
            FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
            FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV4);
            break;

        case FL_CMU_RCHF_FREQUENCY_32MHZ:
            FL_CMU_RCHF_WriteTrimValue(RCHF32M_TRIM);
            FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_1CYCLE);
            FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV4);
            break;

        default:
            FL_CMU_RCHF_WriteTrimValue(RCHF8M_TRIM);
            FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
            FL_CDIF_SetPrescaler(CDIF, FL_CDIF_PSC_DIV1);
            break;
    }

    FL_CMU_RCHF_SetFrequency(clock);
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);
}
