#include "gptim_pwm.h"
#include "fm33lg0xx_fl.h"

void GPTIM_Setup(void)
{
    FL_GPTIM_Enable(GPTIM0);    // 使能定时器
}
