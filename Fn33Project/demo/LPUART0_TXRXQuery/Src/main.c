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
#include "demo_lpuart.h"
#include "fm33_assert.h"



/**
* Chip Series: FM33LG0xx;
* FL Version: v2.2;
* Project Name: LPUART0_TXRXQuery;
* Project Version: v2.2.1.0;
* Create Date: 2022-03-25;
*/


int main(void)
{
    /* Configure the system clock */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    FL_Init();

    /* Initialize all configured peripherals */
    MF_Config_Init();

    FL_DelayMs(3000);//32768 起振时间典型时间1S，最大3S
    FL_CDIF_EnableVAOToCPU(CDIF);//32768信号从VAO传输到CPU

    FL_LPUART_EnableRX(LPUART0);
    FL_LPUART_EnableTX(LPUART0);

    while(1)
    {
        LPUART0_Query();
    }

}


