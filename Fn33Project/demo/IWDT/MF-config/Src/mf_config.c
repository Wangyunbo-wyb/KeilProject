/**
******************************************************************************
* @file           : mf_config.c
* @brief          : MCU FUNCTION CONFIG
******************************************************************************
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
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  GPIO Initialization function
  * @param  void
  * @retval None
  */
void MF_GPIO_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial RCHF */
    FL_CMU_RCHF_SetFrequency(FL_CMU_RCHF_FREQUENCY_8MHZ);
    FL_CMU_RCHF_Enable();

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);    /* 设置FLASH读等待为 0 个周期 */
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);    /* 设置系统主时钟为 RCHF */
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);

    SystemCoreClockUpdate();
}

void MF_Config_Init(void)
{
    /* Initial GPIO */
    MF_GPIO_Init();
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/