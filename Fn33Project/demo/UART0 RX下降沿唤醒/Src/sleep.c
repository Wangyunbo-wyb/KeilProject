#include "sleep.h"
#include "main.h"

// Sleep
void Sleep(void)
{

    FL_RMU_PDR_Enable(RMU);             // 打开PDR
    FL_RMU_BOR_Disable(RMU);            // 关闭BOR 2uA

    FL_VREF_Disable(VREF);              // 关闭VREF1p2

    /* 睡眠电源模式*/
    FL_PMU_SetLowPowerMode(PMU, FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP);
    __WFI();                            //休眠

    FL_VREF_Enable(VREF);               //使能VREF1p2
}

// DeepSleep
void DeepSleep(void)
{

    FL_RMU_PDR_Enable(RMU);             // 打开PDR
    FL_RMU_BOR_Disable(RMU);            // 关闭BOR 2uA

    FL_VREF_Disable(VREF);              // 关闭VREF1p2

    /* 睡眠电源模式*/
    FL_PMU_SetLowPowerMode(PMU, FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP);
    __WFI();                            //休眠

    FL_VREF_Enable(VREF);               //使能VREF1p2
}



