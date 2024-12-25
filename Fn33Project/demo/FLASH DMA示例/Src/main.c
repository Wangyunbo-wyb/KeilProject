#include "main.h"

#define LENGTH  64
uint32_t fBuff[LENGTH];

void Flash_Function(void)
{
    FL_CMU_EnableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_DMA);

    FL_DMA_Enable(DMA);

    FL_FLASH_PageErase(FLASH, 0x00004000);
    memset(fBuff, 0x00, LENGTH * 4);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, fBuff, LENGTH * 4);
    memset(fBuff, 0x55, LENGTH * 4);
    FL_FLASH_Write_Dma(FLASH, 0x00004000, fBuff);
    memset(fBuff, 0x00, LENGTH * 4);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, fBuff, LENGTH * 4);

    FL_FLASH_PageErase(FLASH, 0x00004000);
    memset(fBuff, 0x00, LENGTH * 4);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, fBuff, LENGTH * 4);
    memset(fBuff, 0xAA, LENGTH * 4);
    FL_FLASH_Write_Dma(FLASH, 0x00004000, fBuff);
    memset(fBuff, 0x00, LENGTH * 4);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, fBuff, LENGTH * 4);

    FL_FLASH_PageErase(FLASH, 0x00004000);

    FL_DMA_Disable(DMA);
}

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();

    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();


    Flash_Function();

    while(1)
    {

    }
}


