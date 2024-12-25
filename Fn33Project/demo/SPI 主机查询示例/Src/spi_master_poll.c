#include "spi_master_poll.h"

#define TIMEOUT_VAL     (0xFFFFFFFFUL)

#define LENGTH      16
__USED uint8_t rData[LENGTH] = {0};
__USED uint8_t wData[LENGTH] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                                0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
                               };

uint32_t SPI_ReadWrite(uint32_t data)
{
    uint32_t timeout = 0;

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);

    FL_SPI_WriteTXBuff(SPI1, data);

    do
    {
        timeout++;
    } while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI1) && timeout < TIMEOUT_VAL);

    timeout = 0;
    do
    {
        timeout++;
    } while(!FL_SPI_IsActiveFlag_RXBuffFull(SPI1) && timeout < TIMEOUT_VAL);

    data = FL_SPI_ReadRXBuff(SPI1);

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);

    return data;
}

void SPI_RW_Demo(void)
{
    int i;
    for(i = 0; i < LENGTH; i++)
    {
        rData[i] = SPI_ReadWrite(wData[i]);
    }
}

