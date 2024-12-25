#include "svd.h"

#define SPOWERON    0
#define SPOWEROFF   1

uint8_t SVDState = SPOWERON; //svd检测状态

void SVD_IRQHandler(void)
{
    if(FL_SET == FL_SVD_IsActiveFlag_PowerFall(SVD))        //欠压中断
    {
        FL_SVD_ClearFlag_PowerFall(SVD);
        SVDState = SPOWEROFF;
    }
    else
        if(FL_SET == FL_SVD_IsActiveFlag_PowerRise(SVD))   //欠压恢复中断
        {
            FL_SVD_ClearFlag_PowerRise(SVD);
            SVDState = SPOWERON;
        }
}

void SVD_Setup(void)
{
    FL_SVD_Enable(SVD);
}

void SVD_POLL(void)
{
    if(FL_RESET == FL_SVD_GetLatchedPowerStatus(SVD))   // SVD内部滤波后的电压检测标志，仅在使能数字滤波时有意义；软件避免写此寄存器。
    {
        // SVD检测到欠压
        // ...
    }
}

void SVD_IT(void)
{
    if(SVDState == SPOWEROFF)
    {
        // SVD检测到欠压
    }
    else
    {
        // SVD检测到欠压恢复
    }
}
