#include "gptim_timing.h"

void GPTIM0_1_IRQHandler(void)
{
    if(FL_GPTIM_IsActiveFlag_Update(GPTIM0))
    {
        FL_GPTIM_ClearFlag_Update(GPTIM0);

        // 处理定时中断
    }
}

void GPTIM_Setup(void)
{
    FL_GPTIM_Enable(GPTIM0);
}
