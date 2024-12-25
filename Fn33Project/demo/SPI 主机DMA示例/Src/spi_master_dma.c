#include "spi_master_dma.h"
#include <string.h>

#define LENGTH      16
__USED uint8_t rData[LENGTH] = {0};
__USED uint8_t wData[LENGTH] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
                                0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
                               };

void DMA_IRQHandler(void)
{
    if(FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_5))
    {
        FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_5);

        // 处理接收完成事件
        memset(rData, 0, LENGTH);
    }
}

void SPI_DMARW_Setup(void)
{
    // 打开DMA全局使能
    FL_DMA_Enable(DMA);

    // 配置DMA中断用于通知接收完成，也即传输的完成
    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_5);
    FL_DMA_EnableIT_TransferComplete(DMA, FL_DMA_CHANNEL_5);
}

void SPI_DMARW_Loop(void)
{
    FL_DMA_ConfigTypeDef dma_cfg;

    FL_SPI_Disable(SPI1);

    //必须先使能TX后使能RX
    // 启动DMA TX通道
    dma_cfg.memoryAddress = (uint32_t)wData;
    dma_cfg.transmissionCount = LENGTH - 1;
    FL_DMA_StartTransmission(DMA, &dma_cfg, FL_DMA_CHANNEL_6);

    // 启动DMA RX通道
    dma_cfg.memoryAddress = (uint32_t)rData;
    dma_cfg.transmissionCount = LENGTH - 1;
    FL_DMA_StartTransmission(DMA, &dma_cfg, FL_DMA_CHANNEL_5);

    FL_SPI_Enable(SPI1);
}
