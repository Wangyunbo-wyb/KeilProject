#include "main.h"
#include "led.h"
#include "wwdt.h"

void WDT_IRQHandler(void)
{
    if(FL_WWDT_IsActiveFlag_NearOverflow(WWDT))
    {
        FL_WWDT_ClearFlag_NearOverflow(WWDT);
        FL_WWDT_ReloadCounter(WWDT);
        LED0_TOG();
        return;
    }
}

void WWDT_Init(void)
{
    FL_WWDT_InitTypeDef    WWDT_InitStruct;
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    WWDT_InitStruct.overflowPeriod = FL_WWDT_PERIOD_1024CNT;
    FL_WWDT_Init(WWDT, &WWDT_InitStruct);

    FL_WWDT_ClearFlag_NearOverflow(WWDT);
    FL_WWDT_EnableIT_NearOverflow(WWDT);

    InterruptConfigStruct.preemptPriority = 0x02;
    FL_NVIC_Init(&InterruptConfigStruct, WWDT_IRQn);

}
