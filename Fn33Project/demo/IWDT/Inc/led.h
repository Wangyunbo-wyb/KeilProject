#ifndef __LED_H__
#define __LED_H__

#include "fm33lg0xx_fl.h"

#define LED0_GPIO   GPIOC
#define LED0_PIN    FL_GPIO_PIN_0

#define LED0_ON()   FL_GPIO_ResetOutputPin(LED0_GPIO, LED0_PIN)
#define LED0_OFF()  FL_GPIO_SetOutputPin(LED0_GPIO, LED0_PIN)
#define LED0_TOG()  FL_GPIO_ToggleOutputPin(LED0_GPIO, LED0_PIN)

void LedToggle(uint32_t count);

#endif
