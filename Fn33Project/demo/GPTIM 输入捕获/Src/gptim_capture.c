#include "gptim_capture.h"

// 捕获状态
static uint32_t status = 0UL;
#define IS_CAPTURE          (1 << 0)
#define IS_CAPTURE_OVERFLOW (1 << 1)

// 捕获值
static uint32_t captureValue = 0UL;

void GPTIM0_1_IRQHandler(void)
{
    if(FL_GPTIM_IsActiveFlag_CC(GPTIM0, FL_GPTIM_CHANNEL_1))
    {
        // 保存捕获值
        captureValue = GPTIM0->CCR1;

        status |= IS_CAPTURE;
        FL_GPTIM_ClearFlag_CC(GPTIM0, FL_GPTIM_CHANNEL_1);
    }

    if(FL_GPTIM_IsActiveFlag_CCOverflow(GPTIM0, FL_GPTIM_CHANNEL_1))
    {
        status |= IS_CAPTURE_OVERFLOW;
        FL_GPTIM_ClearFlag_CCOverflow(GPTIM0, FL_GPTIM_CHANNEL_1);
    }
}

void GPTIM_Setup(void)
{
    // 使能GPTIM0
    FL_GPTIM_Enable(GPTIM0);
}

void GPTIM_Loop(void)
{
    if(status & IS_CAPTURE)
    {
        status &= ~IS_CAPTURE;

        //处理捕获值
        (void)captureValue;
    }

    if(status & IS_CAPTURE_OVERFLOW)
    {
        status &= ~IS_CAPTURE_OVERFLOW;

        //捕获溢出事件
        //...
    }
}
