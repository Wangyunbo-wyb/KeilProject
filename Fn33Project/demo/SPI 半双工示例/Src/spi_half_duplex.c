#include "spi_half_duplex.h"

#define TIMEOUT_VAL     (0xFFFFFFFFUL)

void SPI_SetData8Bit(void)
{
    uint32_t timeout = 0;

    do
    {
        timeout++;
    } while(FL_SPI_IsActiveFlag_Busy(SPI1) && timeout < TIMEOUT_VAL);

    FL_SPI_Disable(SPI1);
    FL_SPI_SetDataWidth(SPI1, FL_SPI_DATA_WIDTH_8B);
    FL_SPI_Enable(SPI1);
}

void SPI_SetData16Bit(void)
{
    uint32_t timeout = 0;

    do
    {
        timeout++;
    } while(FL_SPI_IsActiveFlag_Busy(SPI1) && timeout < TIMEOUT_VAL);

    FL_SPI_Disable(SPI1);
    FL_SPI_SetDataWidth(SPI1, FL_SPI_DATA_WIDTH_16B);
    FL_SPI_Enable(SPI1);
}

void SPI_WriteCmd(uint8_t cmd)
{
    uint32_t timeout;

    FL_SPI_SetFrameMode(SPI1, FL_SPI_FRAME_MODE_CMD);
    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);
    FL_SPI_WriteTXBuff(SPI1, cmd);

    // 等待发送缓存空
    timeout = 0;
    do
    {
        timeout++;
    } while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI1) && timeout < TIMEOUT_VAL);

    // 等待发送完成
    timeout = 0;
    do
    {
        timeout++;
    } while(FL_SPI_IsActiveFlag_Busy(SPI1) && timeout < TIMEOUT_VAL);

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);
}

void SPI_WriteData(uint32_t data)
{
    uint32_t timeout;

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);
    FL_SPI_WriteTXBuff(SPI1, data);

    // 等待发送缓存空
    timeout = 0;
    do
    {
        timeout++;
    } while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI1) && timeout < TIMEOUT_VAL);

    // 等待发送完成
    timeout = 0;
    do
    {
        timeout++;
    } while(FL_SPI_IsActiveFlag_Busy(SPI1) && timeout < TIMEOUT_VAL);

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);
}

void SPI_ReadData(uint8_t cmd, uint8_t *data, uint16_t length)
{
    uint32_t timeout;

    FL_SPI_SetFrameMode(SPI1, FL_SPI_FRAME_MODE_CMD);
    FL_SPI_SetTransferDirection(SPI1, FL_SPI_HALF_DUPLEX_RX);
    FL_SPI_ClearRXBuff(SPI1);

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_LOW);

    FL_SPI_WriteTXBuff(SPI1, cmd);

    // 等待发送缓存空
    timeout = 0;
    do
    {
        timeout++;
    } while(!FL_SPI_IsActiveFlag_TXBuffEmpty(SPI1) && timeout < TIMEOUT_VAL);

    while(length--)
    {
        timeout = 0;
        do
        {
            timeout++;
        } while(!FL_SPI_IsActiveFlag_RXBuffFull(SPI1) && timeout < TIMEOUT_VAL);

        *data = FL_SPI_ReadRXBuff(SPI1);
        data++;
    }

    FL_SPI_SetSSNPin(SPI1, FL_SPI_SSN_HIGH);

    FL_SPI_SetTransferDirection(SPI1, FL_SPI_HALF_DUPLEX_TX);
}

void SPI_HalfDuplex_Demo(void)
{
    uint8_t data[2];

    // 发送命令和数据示例
    SPI_WriteCmd(0xA0);
    SPI_WriteData(0xAA);
    SPI_WriteData(0x55);

    // 接收数据示例
    SPI_ReadData(0xB0, data, 2);
    (void) data;
}
