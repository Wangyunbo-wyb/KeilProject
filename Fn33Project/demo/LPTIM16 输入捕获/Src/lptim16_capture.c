#include "lptim16_capture.h"

//捕获状态
static uint32_t status = 0UL;
#define IS_CAPTURE          (1 << 0)
#define IS_CAPTURE_OVERFLOW (1 << 1)

//捕获值
static uint32_t captureValue = 0UL;

//LPTIM16中断服务程序
void LPTIM_IRQHandler(void)
{
    if(FL_LPTIM16_IsActiveFlag_CC(LPTIM16, FL_LPTIM16_CHANNEL_1))
    {
        //保存捕获值
        captureValue = LPTIM16->CCR1;

        status |= IS_CAPTURE;
        FL_LPTIM16_ClearFlag_CC(LPTIM16, FL_LPTIM16_CHANNEL_1);
    }

    if(FL_LPTIM16_IsActiveFlag_CCOverflow(LPTIM16, FL_LPTIM16_CHANNEL_1))
    {
        status |= IS_CAPTURE_OVERFLOW;
        FL_LPTIM16_ClearFlag_CCOverflow(LPTIM16, FL_LPTIM16_CHANNEL_1);
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
