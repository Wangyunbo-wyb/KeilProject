#include "lptim16_timing.h"

//LPTIM16中断服务程序
void LPTIM_IRQHandler(void)
{
    if(FL_LPTIM16_IsActiveFlag_Update(LPTIM16))
    {
        FL_LPTIM16_ClearFlag_Update(LPTIM16);
    }
}

//LPTIM16初始化
void LPTIM16_Setup(void)
{
    /* 使能LPTIM16 */
    FL_LPTIM16_Enable(LPTIM16);
}

//LPTIM16循环
void LPTIM16_Loop(void)
{

}
