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
  * @brief  GPIO Initialization function
  * @param  void
  * @retval None
  */
void MF_GPIO_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;
    FL_GPIO_SetOutputPin(GPIOC, FL_GPIO_PIN_0);

    GPIO_InitStruct.pin = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;

    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


/**
  * @brief  The application entry point.
  * @retval int
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
    MF_GPIO_Init();
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