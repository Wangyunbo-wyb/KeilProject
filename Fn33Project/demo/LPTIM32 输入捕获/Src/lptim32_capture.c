#include "lptim32_capture.h"

//捕获状态
static uint32_t status = 0UL;
#define IS_CAPTURE          (1 << 0)
#define IS_CAPTURE_OVERFLOW (1 << 1)

//捕获值
static uint32_t captureValue = 0UL;

//LPTIM32中断服务程序
void LPTIM_IRQHandler(void)
{
    if(FL_LPTIM32_IsActiveFlag_CC(LPTIM32, FL_LPTIM32_CHANNEL_1))
    {
        //保存捕获值
        captureValue = LPTIM32->CCR1;

        (void)captureValue;

        status |= IS_CAPTURE;
        FL_LPTIM32_ClearFlag_CC(LPTIM32, FL_LPTIM32_CHANNEL_1);
    }

    if(FL_LPTIM32_IsActiveFlag_CCOverflow(LPTIM32, FL_LPTIM32_CHANNEL_1))
    {
        status |= IS_CAPTURE_OVERFLOW;
        FL_LPTIM32_ClearFlag_CCOverflow(LPTIM32, FL_LPTIM32_CHANNEL_1);
    }
}

void LPTIM32_Setup(void)
{
    /* 使能LPTIM32 */
    FL_LPTIM32_Enable(LPTIM32);
}

void LPTIM32_Loop(void)
{
    if(status & IS_CAPTURE)
    {
        status &= ~IS_CAPTURE;

        //捕获事件
        //...
    }

    if(status & IS_CAPTURE_OVERFLOW)
    {
        status &= ~IS_CAPTURE_OVERFLOW;

        //捕获溢出事件
        //...
    }
}
