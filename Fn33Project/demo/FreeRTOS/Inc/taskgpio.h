#ifndef __TASKGPIO_H__
#define __TASKGPIO_H__

#include "main.h"

extern void GPIOTask(void *pvParameters);
extern void GPIO_IRQCallBack(void);
extern uint32_t RunTimeTicks;
extern void BaseTime(void);
#endif
