#include "atim.h"
#include "main.h"

void ATIM_IRQHandler()
{
    if(FL_ATIM_IsEnabledIT_Update(ATIM) && FL_ATIM_IsActiveFlag_Update(ATIM))
    {
        FL_ATIM_ClearFlag_Update(ATIM);

        //处理更新事件
    }
}

void ATIM_Start()
{
    //使能LATIM
    FL_ATIM_Enable(ATIM);
}


