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
  * @brief  SVD Initialization function
  * @param  void
  * @retval None
  */
void MF_SVD_Init(void)
{
    FL_SVD_InitTypeDef    SVD_InitStruct;

    SVD_InitStruct.SVSChannel = FL_DISABLE;
    SVD_InitStruct.digitalFilter = FL_ENABLE;
    SVD_InitStruct.referenceVoltage = FL_SVD_REFERENCE_1P0V;
    SVD_InitStruct.workMode = FL_SVD_WORK_MODE_CONTINUOUS;
    SVD_InitStruct.enablePeriod = FL_SVD_ENABLE_PERIOD_62P5MS;
    SVD_InitStruct.warningThreshold = FL_SVD_WARNING_THRESHOLD_GROUP7;

    FL_SVD_Init(SVD, &SVD_InitStruct);
}

/**
  * @brief  SVD Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_SVD_Interrupt_Init(void)
{
    FL_SVD_ClearFlag_PowerFall(SVD);
    FL_SVD_EnableIT_PowerFall(SVD);

    FL_SVD_ClearFlag_PowerRise(SVD);
    FL_SVD_EnableIT_PowerRise(SVD);
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
    FL_NVIC_Init(&InterruptConfigStruct, SVD_IRQn);
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial RCHF */
    FL_CMU_RCHF_SetFrequency(FL_CMU_RCHF_FREQUENCY_8MHZ);                               /*配置RCHF频率*/
    FL_CMU_RCHF_Enable();                                                               /*使能RCHF*/

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);                             /*配置FLASH等待周期*/
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);                         /*配置系统时钟*/
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);                                     /*配置AHB时钟*/
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);                                     /*配置APB时钟*/

    SystemCoreClockUpdate();                                                            /*系统时钟更新*/
}

void MF_Config_Init(void)
{
    /* Initial SVD */
    MF_SVD_Init();
    MF_SVD_Interrupt_Init();

    /* Initial NVIC */
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
