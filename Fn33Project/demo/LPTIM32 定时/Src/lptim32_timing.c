#include "lptim32_timing.h"

//LPTIM32中断服务程序
void LPTIM_IRQHandler(void)
{
    if(FL_LPTIM32_IsEnabledIT_Update(LPTIM32) && FL_LPTIM32_IsActiveFlag_Update(LPTIM32))
    {
        FL_LPTIM32_ClearFlag_Update(LPTIM32);
    }
}

void LPTIM32_Setup(void)
{
    FL_LPTIM32_Enable(LPTIM32);
}

void LPTIM32_Loop(void)
{
    /* Do nothing */
}
