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
#include "vao.h"
#include "fout.h"

/**
* Chip Series: FM33LG0xx;
* FL Version: v2.2;
* Project Name: VAO_XTLF;
* Project Version: v2.2.1.0;
* Create Date: 2022-05-07;
*/

int main(void)
{
    /* Configure the system clock */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    FL_Init();

    /* Initialize all configured peripherals */
    MF_Config_Init();

    XTLFConfig();

    FoutInit();

    while(1)
    {

    }
}
