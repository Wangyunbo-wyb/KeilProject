#include "crc.h"

__STATIC_INLINE uint8_t CRC7_MMC(uint8_t *data, uint32_t length)
{
    while(length--)
    {
        FL_CRC_WriteData(CRC, *data++);

        while(FL_CRC_IsActiveFlag_Busy(CRC));
    }

    return FL_CRC_ReadData(CRC) & 0x7f;
}

__STATIC_INLINE uint8_t CRC8(uint8_t *data, uint32_t length)
{
    while(length--)
    {
        FL_CRC_WriteData(CRC, *data++);

        while(FL_CRC_IsActiveFlag_Busy(CRC));
    }

    return FL_CRC_ReadData(CRC) & 0xff;
}

__STATIC_INLINE uint16_t CRC16_CCITT(uint8_t *data, uint32_t length)
{
    while(length--)
    {
        FL_CRC_WriteData(CRC, *data++);

        while(FL_CRC_IsActiveFlag_Busy(CRC));
    }

    return FL_CRC_ReadData(CRC) & 0xffff;
}

__STATIC_INLINE uint32_t CRC32(uint8_t *data, uint32_t length)
{
    while(length--)
    {
        FL_CRC_WriteData(CRC, *data++);

        while(FL_CRC_IsActiveFlag_Busy(CRC));
    }

    return FL_CRC_ReadData(CRC);
}

__STATIC_INLINE uint16_t CRC16_CCITT_WORD(uint32_t *data, uint32_t length)
{
    while(length--)
    {
        FL_CRC_WriteData(CRC, *data++);

        while(FL_CRC_IsActiveFlag_Busy(CRC));
    }

    return FL_CRC_ReadData(CRC) & 0xffff;
}


__STATIC_INLINE uint16_t CRC16_CCITT_DMA(uint8_t *data, uint32_t length)
{
    FL_DMA_ConfigTypeDef DMA_ConfigStruct;

    DMA_ConfigStruct.memoryAddress = (uint32_t)data;
    DMA_ConfigStruct.transmissionCount = length - 1;
    FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_0);
    FL_DMA_Enable(DMA);
    while(!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0));
    FL_DMA_Disable(DMA);

    return FL_CRC_ReadData(CRC) & 0xffff;
}

__STATIC_INLINE uint16_t CRC16_CCITT_WORD_DMA(uint32_t *data, uint32_t length)
{
    FL_DMA_ConfigTypeDef DMA_ConfigStruct;

    DMA_ConfigStruct.memoryAddress = (uint32_t)data;
    DMA_ConfigStruct.transmissionCount = length - 1;
    FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_0);
    FL_DMA_Enable(DMA);
    while(!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0));
    FL_DMA_Disable(DMA);

    return FL_CRC_ReadData(CRC) & 0xffff;
}



#define DATA_LENGTH     8
static uint8_t DATA[DATA_LENGTH] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

#define DATA1_LENGTH    2
static uint32_t DATA1[DATA1_LENGTH] = {0x01020304, 0x05060708};

FL_ErrorStatus CRC7_MMC_Cal(void)
{
    uint32_t result = 0;
    result = CRC7_MMC(DATA, DATA_LENGTH);

    if(result != 0x57) { return FL_FAIL; }

    return FL_PASS;
}

FL_ErrorStatus CRC8_Cal(void)
{
    uint32_t result = 0;
    result = CRC8(DATA, DATA_LENGTH);

    if(result != 0x3E) { return FL_FAIL; }

    return FL_PASS;
}

FL_ErrorStatus CRC16_CCITT_Cal(void)
{
    uint32_t result = 0;
    result = CRC16_CCITT(DATA, DATA_LENGTH);

    if(result != 0xEEA7) { return FL_FAIL; }

    return FL_PASS;
}

FL_ErrorStatus CRC32_Cal(void)
{
    uint32_t result = 0;
    result = CRC32(DATA, DATA_LENGTH);

    if(result != 0x3FCA88C5) { return FL_FAIL; }

    return FL_PASS;
}

FL_ErrorStatus CRC16_CCITT_WORD_Cal(void)
{
    uint32_t result = 0;
    result = CRC16_CCITT_WORD(DATA1, DATA1_LENGTH);

    if(result != 0xEEA7) { return FL_FAIL; }

    return FL_PASS;
}

FL_ErrorStatus CRC16_CCITT_DMA_Cal(void)
{
    uint32_t result = 0;
    result = CRC16_CCITT_DMA(DATA, DATA_LENGTH);

    if(result != 0xEEA7) { return FL_FAIL; }

    return FL_PASS;
}

FL_ErrorStatus CRC16_CCITT_WORD_DMA_Cal(void)
{
    uint32_t result = 0;
    result = CRC16_CCITT_WORD_DMA(DATA1, DATA1_LENGTH);

    if(result != 0xEEA7) { return FL_FAIL; }

    return FL_PASS;
}
