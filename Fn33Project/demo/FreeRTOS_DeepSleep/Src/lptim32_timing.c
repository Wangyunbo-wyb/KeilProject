#include "lptim32_timing.h"

void LPTIM32_Init(void)
{
    FL_LPTIM32_InitTypeDef    TimerBase_InitStruct;

    TimerBase_InitStruct.clockSource = FL_CMU_LPTIM32_CLK_SOURCE_LSCLK;
    TimerBase_InitStruct.prescalerClockSource = FL_LPTIM32_CLK_SOURCE_INTERNAL;
    TimerBase_InitStruct.prescaler = FL_LPTIM32_PSC_DIV32;
    TimerBase_InitStruct.autoReload = 0xFFFFFFFF;
    TimerBase_InitStruct.mode = FL_LPTIM32_OPERATION_MODE_NORMAL;
    TimerBase_InitStruct.onePulseMode = FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS;
    TimerBase_InitStruct.triggerEdge = FL_LPTIM32_ETR_TRIGGER_EDGE_RISING;
    TimerBase_InitStruct.countEdge = FL_LPTIM32_ETR_COUNT_EDGE_RISING;

    FL_LPTIM32_Init(LPTIM32, &TimerBase_InitStruct);
}

