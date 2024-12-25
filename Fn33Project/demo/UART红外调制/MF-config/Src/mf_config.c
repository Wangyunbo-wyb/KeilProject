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
  * @brief  UART0 Initialization function
  * @param  void
  * @retval None
  */
void MF_UART0_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_UART_InitTypeDef    UART0_InitStruct;

    GPIO_InitStruct.pin          = FL_GPIO_PIN_14;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_DISABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    UART0_InitStruct.clockSrc          = FL_CMU_UART0_CLK_SOURCE_APBCLK;
    UART0_InitStruct.baudRate          = 2400;
    UART0_InitStruct.transferDirection = FL_UART_DIRECTION_TX;
    UART0_InitStruct.dataWidth         = FL_UART_DATA_WIDTH_8B;
    UART0_InitStruct.stopBits          = FL_UART_STOP_BIT_WIDTH_1B;
    UART0_InitStruct.parity            = FL_UART_PARITY_NONE;

    (void)FL_UART_Init(UART0, &UART0_InitStruct);
}

/**
  * @brief  UART0_InfraredModulate Initialization function
  * @param  void
  * @retval None
  */
void MF_UART0_InfraredModulate_Init(void)
{
    FL_UART_InfraRed_InitTypeDef    InfraredModulate_InitStruct;

    InfraredModulate_InitStruct.polarity            = FL_UART_INFRARED_POLARITY_NORMAL;
    InfraredModulate_InitStruct.modulationDuty      = 50;
    InfraredModulate_InitStruct.modulationFrequency = 38000;

    (void)FL_UART_InfraRed_Init(UART0, &InfraredModulate_InitStruct);
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
    /* Initial UART0 */
    MF_UART0_Init();
    MF_UART0_InfraredModulate_Init();
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
