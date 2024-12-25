#include "dac.h"


void DAC_SWTrigger(void)
{
    FL_DAC_Enable(DAC);
    FL_DAC_WriteData(DAC, 2047);
    FL_DAC_EnableSoftwareTrigger(DAC);
}

