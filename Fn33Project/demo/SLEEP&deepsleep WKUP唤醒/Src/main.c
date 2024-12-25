/**
  ****************************************************************************************************
  * @file    main.c
  * @author  FMSH Application Team
  * @brief   Header file of FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */

#include "main.h"
#include "sleep.h"
#include "wkup_interrupt.h"

/**
* Chip Series: FM33LG0xx;
* FL Version: v2.2;
* Project Name: SLEEP_WKUPInterrupt;
* Project Version: v2.2.1.0;
* Create Date: 2022-05-07;
*/
uint8_t i;

void LED_Init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.pin          = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_DISABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    FL_GPIO_SetOutputPin(GPIOC,FL_GPIO_PIN_0);
}

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();

    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();

    WKUP_Interrupt_Init();
    LED_Init();
    while(1)
    {
        DeepSleep();
        for(i = 0; i < 5; i++)
        {
            FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
            FL_DelayMs(500);
        }
    }
}


