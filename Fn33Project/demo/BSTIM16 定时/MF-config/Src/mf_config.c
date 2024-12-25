/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : mf_config.c
  * @brief          : MCU FUNCTION CONFIG
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 FMSH.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by FMSH under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "mf_config.h"
#include "fm33lg0xx_fl.h"

/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  BSTIM16_TimerBase Initialization function
  * @param  void
  * @retval None
  */
void MF_BSTIM16_TimerBase_Init(void)
{
    FL_BSTIM16_InitTypeDef    TimerBase_InitStruct;

    TimerBase_InitStruct.prescaler = 7999;
    TimerBase_InitStruct.autoReload = 999;
    TimerBase_InitStruct.autoReloadState = FL_ENABLE;
    TimerBase_InitStruct.clockSource = FL_CMU_BSTIM16_CLK_SOURCE_APBCLK;

    FL_BSTIM16_Init(BSTIM16, &TimerBase_InitStruct);
}

/**
  * @brief  BSTIM16 Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_BSTIM16_Interrupt_Init(void)
{
    FL_BSTIM16_ClearFlag_Update(BSTIM16);
    FL_BSTIM16_EnableIT_Update(BSTIM16);
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
    FL_NVIC_Init(&InterruptConfigStruct, BSTIM_IRQn);
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial RCHF */
    FL_CMU_RCHF_WriteTrimValue(RCHF8M_TRIM);
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
    /* Initial BSTIM16 */
    MF_BSTIM16_TimerBase_Init();
    MF_BSTIM16_Interrupt_Init();

    /* Initial NVIC */
    MF_NVIC_Init();
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
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
    /* USER CODE BEGIN Assert_Failed */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END Assert_Failed */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
