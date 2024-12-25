#include "led.h"

void LedToggle(uint32_t count)
{
    uint32_t i = 0;
    for(i = 0; i < count; i++)
    {
        LED0_ON();
        FL_DelayMs(100);
        LED0_OFF();
        FL_DelayMs(100);
    }
}
