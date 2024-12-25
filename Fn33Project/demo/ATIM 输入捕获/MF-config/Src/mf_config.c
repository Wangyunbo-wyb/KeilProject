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
  * @brief  ATIM_TimerBase Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_TimerBase_Init(void)
{
    FL_ATIM_InitTypeDef    TimerBase_InitStruct;

    TimerBase_InitStruct.clockSource = FL_CMU_ATIM_CLK_SOURCE_APBCLK;
    TimerBase_InitStruct.prescaler = 7;
    TimerBase_InitStruct.counterMode = FL_ATIM_COUNTER_DIR_UP;
    TimerBase_InitStruct.autoReload = 0xFFFF - 1;
    TimerBase_InitStruct.clockDivision = FL_ATIM_CLK_DIVISION_DIV1;
    TimerBase_InitStruct.repetitionCounter = 0;
    TimerBase_InitStruct.autoReloadState = FL_DISABLE;

    FL_ATIM_Init(ATIM, &TimerBase_InitStruct);
}

/**
  * @brief  ATIM_Channel1 Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_Channel1_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ATIM_IC_InitTypeDef    ATIM_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_4;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    ATIM_InitStruct.captureState = FL_ENABLE;
    ATIM_InitStruct.ICPolarity = FL_ATIM_IC_POLARITY_NORMAL;
    ATIM_InitStruct.ICActiveInput = FL_ATIM_CHANNEL_MODE_INPUT_NORMAL;
    ATIM_InitStruct.ICPrescaler = FL_ATIM_IC_PSC_DIV1;
    ATIM_InitStruct.ICFilter = FL_ATIM_IC_FILTER_DIV1;

    FL_ATIM_IC_Init(ATIM, FL_ATIM_CHANNEL_1, &ATIM_InitStruct);
}


/**
  * @brief  ATIM Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_ATIM_Interrupt_Init(void)
{
    FL_ATIM_ClearFlag_Update(ATIM);
    FL_ATIM_EnableIT_Update(ATIM);

    FL_ATIM_ClearFlag_CC(ATIM, FL_ATIM_CHANNEL_1);
    FL_ATIM_EnableIT_CC(ATIM, FL_ATIM_CHANNEL_1);
}

/**
  * @brief  NVIC Initialization function
  * @param  void
  * @retval None
  */
void MF_NVIC_Init(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 0x02;
    FL_NVIC_Init(&InterruptConfigStruct, ATIM_IRQn);
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
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);

    SystemCoreClockUpdate();
}

void MF_Config_Init(void)
{
    /* Initial ATIM */
    MF_ATIM_TimerBase_Init();
    MF_ATIM_Channel1_Init();
    MF_ATIM_Interrupt_Init();
    MF_NVIC_Init();

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
