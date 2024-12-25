#include "fout.h"
#include "fm33lg0xx_fl.h"

void FoutInit(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.pin             = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode            = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType      = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull            = FL_DISABLE;
    GPIO_InitStruct.remapPin        = FL_DISABLE;
    GPIO_InitStruct.analogSwitch    = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    FL_GPIO_SetFOUT0(GPIO, FL_GPIO_FOUT0_SELECT_AHBCLK_DIV64);
}
