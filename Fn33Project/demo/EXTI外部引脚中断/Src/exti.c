#include "main.h"
#include "exti.h"

uint32_t EXTIFlag = 0;
/*引脚中断处理函数*/
void GPIO_IRQHandler(void)
{
    if(FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_9) == 0x01UL)
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_9);
        EXTIFlag = 1;
    }
}

void EXTI_Interrupt_Handle(void)
{
    if(EXTIFlag == 1)
    {
        EXTIFlag = 0;
        /*用户处理程序*/

    }
}
