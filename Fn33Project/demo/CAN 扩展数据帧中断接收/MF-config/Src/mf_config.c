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
  * @brief  CAN Initialization function
  * @param  void
  * @retval None
  */
void MF_CAN_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_CAN_InitTypeDef    CAN_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_10;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_InitStruct.pin = FL_GPIO_PIN_9;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    CAN_InitStruct.SJW = FL_CAN_SJW_2Tq;
    CAN_InitStruct.TS1 = FL_CAN_TS1_9Tq;
    CAN_InitStruct.TS2 = FL_CAN_TS2_6Tq;
    CAN_InitStruct.BRP = 3;
    CAN_InitStruct.clockSource = FL_CMU_CAN_CLK_SOURCE_XTHF;

    FL_CAN_Init(CAN, &CAN_InitStruct);
}

/**
  * @brief  CAN_Filter_FL_CAN_FILTER1 Initialization function
  * @param  void
  * @retval None
  */
void MF_CAN_Filter_FL_CAN_FILTER1_Init(void)
{
    FL_CAN_FilterInitTypeDef    Filter_InitStruct;

    Filter_InitStruct.filterIdSRR = FL_CAN_SRR_BIT_HIGH;
    Filter_InitStruct.filterIdIDE = FL_CAN_IDE_BIT_HIGH;
    Filter_InitStruct.filterIdRTR = FL_CAN_RTR_BIT_LOW;
    Filter_InitStruct.filterEn = FL_ENABLE;
    Filter_InitStruct.filterIdStandard = 0x00;
    Filter_InitStruct.filterIdExtend = 0x1AB55993;
    Filter_InitStruct.filterMaskIdHigh = 0X7FF;
    Filter_InitStruct.filterMaskIdSRR = FL_ENABLE;
    Filter_InitStruct.filterMaskIdIDE = FL_ENABLE;
    Filter_InitStruct.filterMaskIdLow = 0X3FFFF;
    Filter_InitStruct.filterMaskIdRTR = FL_ENABLE;

    FL_CAN_FilterInit(CAN, &Filter_InitStruct, FL_CAN_FILTER2);
}

/**
  * @brief  CAN Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_CAN_Interrupt_Init(void)
{
    FL_CAN_ClearFlag_RXOK(CAN);
    FL_CAN_EnableIT_RXOK(CAN);
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
    FL_NVIC_Init(&InterruptConfigStruct, CAN_IRQn);
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};
		
    /*PC2.3配置为模拟功能，外接XTHF*/
    GPIO_InitStruct.pin        = FL_GPIO_PIN_2 | FL_GPIO_PIN_3;
    GPIO_InitStruct.mode       = FL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull       = FL_DISABLE;
    GPIO_InitStruct.remapPin   = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*XTHF振荡强度配置*/
    FL_CMU_XTHF_WriteDriverStrength(0x0A);  
    /*使能XTHF*/
    FL_CMU_XTHF_Enable();
	/*硬件延时等待XTHF稳定建立*/
    FL_DelayMs(2);
    /* Initial RCHF */
    FL_CMU_RCHF_SetFrequency(FL_CMU_RCHF_FREQUENCY_8MHZ);
    FL_CMU_RCHF_Enable();
    

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_XTHF);
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);

    SystemCoreClockUpdate();
}

void MF_Config_Init(void)
{
    /* Initial CAN */
    MF_CAN_Init();
    MF_CAN_Filter_FL_CAN_FILTER1_Init();
    MF_CAN_Interrupt_Init();

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
