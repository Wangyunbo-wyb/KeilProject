#include "main.h"

uint32_t ProgAddr = 0x00004000;
uint32_t DataToWrite[128];

void Flash_Function(void)
{
    FL_FLASH_PageErase(FLASH, 0x00004000);
    memset(DataToWrite, 0x55, 512);
    FL_FLASH_Program_Word(FLASH, ProgAddr, DataToWrite[0]);

    FL_FLASH_PageErase(FLASH, 0x00004000);
    memset(DataToWrite, 0xAA, 512);
    FL_FLASH_Program_Page(FLASH, ProgAddr / FL_FLASH_PGAE_SIZE_BYTE, DataToWrite);

    FL_FLASH_SectorErase(FLASH, 0x00004000);
    memset(DataToWrite, 0x00, 512);
    FL_FLASH_Program_Sector(FLASH, ProgAddr / FL_FLASH_SECTOR_SIZE_BYTE, DataToWrite);

    FL_FLASH_SectorErase(FLASH, 0x00004000);
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


