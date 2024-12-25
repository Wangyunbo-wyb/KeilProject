#include "bstim16_timing.h"

void BSTIM16_Start(void)
{
    //使能BSTIM32
    FL_BSTIM16_Enable(BSTIM16);
}


void BSTIM_IRQHandler(void)
{
    if(FL_BSTIM16_IsEnabledIT_Update(BSTIM16) && FL_BSTIM16_IsActiveFlag_Update(BSTIM16))
    {
        FL_BSTIM16_ClearFlag_Update(BSTIM16);

        // 处理更新事件
        // ...
    }
}
