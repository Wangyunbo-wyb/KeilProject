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
  * @brief  LPTIM16_TimerBase Initialization function
  * @param  void
  * @retval None
  */
void MF_LPTIM16_TimerBase_Init(void)
{
    FL_LPTIM16_InitTypeDef    TimerBase_InitStruct;

    TimerBase_InitStruct.clockSource = FL_CMU_LPTIM16_CLK_SOURCE_APBCLK;
    TimerBase_InitStruct.prescalerClockSource = FL_LPTIM16_CLK_SOURCE_INTERNAL;
    TimerBase_InitStruct.prescaler = FL_LPTIM16_PSC_DIV8;
    TimerBase_InitStruct.autoReload = 999;
    TimerBase_InitStruct.mode = FL_LPTIM16_OPERATION_MODE_NORMAL;
    TimerBase_InitStruct.onePulseMode = FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS;
    TimerBase_InitStruct.triggerEdge = FL_LPTIM16_ETR_TRIGGER_EDGE_RISING;
    TimerBase_InitStruct.countEdge = FL_LPTIM16_ETR_COUNT_EDGE_RISING;
    TimerBase_InitStruct.encoderMode = FL_LPTIM16_ENCODER_MODE_TI2FP2_CNT_TI1FP1_CNT;

    FL_LPTIM16_Init(LPTIM16, &TimerBase_InitStruct);
}

/**
  * @brief  LPTIM16_Channel1 Initialization function
  * @param  void
  * @retval None
  */
void MF_LPTIM16_Channel1_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_LPTIM16_IC_InitTypeDef    LPTIM16_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_13;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    LPTIM16_InitStruct.ICInputPolarity = FL_LPTIM16_IC_POLARITY_NORMAL;
    LPTIM16_InitStruct.ICInputDigitalFilter = FL_ENABLE;
    LPTIM16_InitStruct.channel1Prescaler = 0;
    LPTIM16_InitStruct.channel1CaptureSource = FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0;
    LPTIM16_InitStruct.ICEdge = FL_LPTIM16_IC_EDGE_FALLING;

    FL_LPTIM16_IC_Init(LPTIM16, FL_LPTIM16_CHANNEL_1, &LPTIM16_InitStruct);
}

/**
  * @brief  LPTIM16_Channel2 Initialization function
  * @param  void
  * @retval None
  */
void MF_LPTIM16_Channel2_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_LPTIM16_IC_InitTypeDef    LPTIM16_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_14;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_ENABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    LPTIM16_InitStruct.ICInputPolarity = FL_LPTIM16_IC_POLARITY_NORMAL;
    LPTIM16_InitStruct.ICInputDigitalFilter = FL_ENABLE;
    LPTIM16_InitStruct.channel1Prescaler = 0;
    LPTIM16_InitStruct.channel1CaptureSource = FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0;
    LPTIM16_InitStruct.ICEdge = FL_LPTIM16_IC_EDGE_FALLING;

    FL_LPTIM16_IC_Init(LPTIM16, FL_LPTIM16_CHANNEL_2, &LPTIM16_InitStruct);
}

/**
  * @brief  LPTIM16 Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_LPTIM16_Interrupt_Init(void)
{
    FL_LPTIM16_ClearFlag_Update(LPTIM16);
    FL_LPTIM16_EnableIT_Update(LPTIM16);
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
    FL_NVIC_Init(&InterruptConfigStruct, LPTIMx_IRQn);
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
    /* Initial LPTIM16 */
    MF_LPTIM16_TimerBase_Init();
    MF_LPTIM16_Channel1_Init();
    MF_LPTIM16_Channel2_Init();
    MF_LPTIM16_Interrupt_Init();

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
