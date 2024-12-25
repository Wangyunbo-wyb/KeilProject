#include "lptim16_encoder.h"
#include "fm33lg0xx_fl.h"

// 捕获值
static int32_t encoderRoundCnt = 0UL;

// LPTIM16中断服务程序
void LPTIM_IRQHandler(void)
{
    // 定时器溢出时增加计数
    if(FL_LPTIM16_IsActiveFlag_Update(LPTIM16))
    {
        FL_LPTIM16_ClearFlag_Update(LPTIM16);

        if(FL_LPTIM16_ReadCounter(LPTIM16) >= (FL_LPTIM16_ReadAutoReload(LPTIM16) / 2))
        {
            encoderRoundCnt--;
        }

        else
        {
            encoderRoundCnt++;
        }
    }
}

void LPTIM16_Setup(void)
{
    /* 使能LPTIM16 */
    FL_LPTIM16_Enable(LPTIM16);
}

void LPTIM16_Loop(void)
{
    /* 获取编码器计数值 */
    volatile int64_t cnt = (int64_t)encoderRoundCnt * FL_LPTIM16_ReadAutoReload(LPTIM16) +
                           FL_LPTIM16_ReadCounter(LPTIM16);
}
