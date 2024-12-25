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

    GPIO_InitStruct.pin          = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_DISABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
  * @brief  U7816 Initialization function
  * @param  void
  * @retval None
  */
void MF_U7816_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_U7816_InitTypeDef    U7816_InitStruct;
    //CLK
    GPIO_InitStruct.pin          = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_ENABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    //IO
    GPIO_InitStruct.pin          = FL_GPIO_PIN_12;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_ENABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    U7816_InitStruct.baud                = 371;
    U7816_InitStruct.blockGuard          = FL_DISABLE;
    U7816_InitStruct.errorGuardTime      = FL_U7816_ERROR_GUARD_TIME_1ETU;
    U7816_InitStruct.errorSignalWidth    = FL_U7816_ERROR_SIGNAL_WIDTH_2ETU;
    U7816_InitStruct.extraGuardTime      = 0;
    U7816_InitStruct.outputClockFrequency = 4000000;
    U7816_InitStruct.rxAutoErrorSignal   = FL_ENABLE;
    U7816_InitStruct.parity              = FL_U7816_PARITY_EVEN;
    U7816_InitStruct.txAutoRetry         = FL_ENABLE;
    U7816_InitStruct.retryCnt            = FL_U7816_RETRY_COUNT_1;
    U7816_InitStruct.rxGuardTime         = FL_U7816_RX_GUARD_TIME_2ETU;
    U7816_InitStruct.transferOrder       = FL_U7816_BIT_ORDER_LSB_FIRST;

    (void)FL_U7816_Init(U7816, &U7816_InitStruct);
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /*ClockTree Configuration*/
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

    /* Initial U7816 */
    MF_U7816_Init();
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
