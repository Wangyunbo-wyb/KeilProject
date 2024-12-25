#include "dac.h"



void DAC_Out(void)
{
    FL_DAC_WriteData(DAC, 2047);                  /*配置DAC默认状态*/
    FL_DAC_Enable(DAC);

}


