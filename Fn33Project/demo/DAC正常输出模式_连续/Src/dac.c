#include "dac.h"



void DAC_Out(void)
{
    FL_DAC_WriteData(DAC, 2047);       /*еДжцDACд╛хов╢л╛*/
    FL_DAC_Enable(DAC);

}


