#include "gptim_dmaburst_pwm.h"
#include "fm33lg0xx_fl.h"

void GPTIM_Setup(void)
{
    // 设置GPTIM1的DMA Burst，一次性更新CCR1~CCR4
    FL_GPTIM_SetDMABurstAddress(GPTIM1, FL_GPTIM_DMA_BURST_ADDR_CCR1);
    FL_GPTIM_SetDMABurstLength(GPTIM1, FL_GPTIM_DMA_BURST_LENGTH_4);

    // 启动GPTIM1
    FL_GPTIM_Enable(GPTIM1);

    // 打开DMA全局使能
    FL_DMA_Enable(DMA);
}

// DMA Burst主循环，输出4路占空比交替变化的PWM，可以外接LED观察呼吸流水灯现象
void GPTIM_Loop(void)
{
    FL_DMA_ConfigTypeDef dma_cfg;
    static uint32_t data[4] = {200, 400, 600, 800};
    static uint32_t dir[4] = {1, 1, 1, 1};

    // 更新各个LED亮度
    int i;
    for(i = 0; i < 4; i++)
    {
        if(dir[i])
        { data[i] += 50; }
        else
        { data[i] -= 50; }

        if(data[i] >= 1000) { dir[i] = 0; }
        else
            if(data[i] <= 50) { dir[i] = 1; }
    }

    // 启动DMA Burst写入CCR数据
		FL_GPTIM_EnableDMAReq_Update(GPTIM1);
    dma_cfg.memoryAddress = (uint32_t)data;
    dma_cfg.transmissionCount = 4 - 1;
    FL_DMA_StartTransmission(DMA, &dma_cfg, FL_DMA_CHANNEL_6);
    while(!FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_6));
		FL_GPTIM_DisableDMAReq_Update(GPTIM1);

    // 延时用于控制呼吸流水灯变化速度
    FL_DelayMs(25);
}
