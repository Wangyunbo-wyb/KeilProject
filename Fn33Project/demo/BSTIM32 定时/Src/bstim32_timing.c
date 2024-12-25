#include "bstim32_timing.h"

void BSTIM32_Start(void)
{
    //使能BSTIM32
    FL_BSTIM32_Enable(BSTIM32);
}


void BSTIM_IRQHandler(void)
{
    if(FL_BSTIM32_IsEnabledIT_Update(BSTIM32) && FL_BSTIM32_IsActiveFlag_Update(BSTIM32))
    {
        FL_BSTIM32_ClearFlag_Update(BSTIM32);

        // 处理更新事件
        // ...
    }
}
