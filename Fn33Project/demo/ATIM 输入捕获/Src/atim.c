#include "atim.h"
#include "main.h"

// 捕获状态
static uint8_t captureStatus = 0;
// 触发捕获前定时器溢出的次数
static uint32_t captureOverflowCount = 0;
uint32_t  capturedValue;

void ATIM_Start(void)
{
    //使能ATIM
    FL_ATIM_Enable(ATIM);
}


//PWM输入捕捉
void ATIM_Loop()
{
    /* 循环调用，当触发捕获时记录捕获值并重新开始捕获 */
    if(captureStatus)
    {
        // 实际捕获值 = 定时器捕获期间溢出次数 * 定时周期 + 当前捕获值
        capturedValue = captureOverflowCount * FL_ATIM_ReadAutoReload(ATIM) + FL_ATIM_ReadCompareCH1(ATIM);

        // 处理数据ATIM
        // ...

        // 重新开始捕获
        captureStatus = 0;
        captureOverflowCount = 0;
        FL_ATIM_Enable(ATIM);
    }


}

void ATIM_IRQHandler()
{
    if(FL_ATIM_IsEnabledIT_Update(ATIM) && FL_ATIM_IsActiveFlag_Update(ATIM))
    {
        FL_ATIM_ClearFlag_Update(ATIM);

        // 处理更新事件
        captureOverflowCount++;
        // ...
    }

    if(FL_ATIM_IsEnabledIT_CC(ATIM, FL_ATIM_CHANNEL_1) && FL_ATIM_IsActiveFlag_CC(ATIM, FL_ATIM_CHANNEL_1))
    {
        FL_ATIM_ClearFlag_CC(ATIM, FL_ATIM_CHANNEL_1);

        // 停止捕获
        FL_ATIM_Disable(ATIM);

        // 处理捕获事件
        captureStatus = 1;
        // ...
    }
}

