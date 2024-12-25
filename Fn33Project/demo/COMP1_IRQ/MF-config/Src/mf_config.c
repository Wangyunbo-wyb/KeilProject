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
  * @brief  COMP1 Initialization function
  * @param  void
  * @retval None
  */
void MF_COMP1_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_COMP_InitTypeDef    COMP1_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_8;                                                  /*配置GPIO的引脚号*/
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;                                           /*配置GPIO的功能模式*/
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;                                 /*配置GPIO的输出模式*/
    GPIO_InitStruct.pull = FL_DISABLE;                                                    /*配置GPIO输上拉模式*/
    GPIO_InitStruct.remapPin = FL_DISABLE;                                                /*配置GPIO数字重定向功能*/
    GPIO_InitStruct.analogSwitch = FL_DISABLE;                                            /*配置GPIO模拟开关功能*/
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);                                                /*GPIO初始化*/

    GPIO_InitStruct.pin = FL_GPIO_PIN_10;                                                  /*配置GPIO的引脚号*/
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;                                           /*配置GPIO的功能模式*/
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;                                 /*配置GPIO的输出模式*/
    GPIO_InitStruct.pull = FL_DISABLE;                                                    /*配置GPIO输上拉模式*/
    GPIO_InitStruct.remapPin = FL_DISABLE;                                                /*配置GPIO数字重定向功能*/
    GPIO_InitStruct.analogSwitch = FL_DISABLE;                                            /*配置GPIO模拟开关功能*/
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    COMP1_InitStruct.edge = FL_COMP_INTERRUPT_EDGE_BOTH;                                  /*配置COMP中断沿*/
    COMP1_InitStruct.polarity = FL_COMP_OUTPUT_POLARITY_NORMAL;                           /*配置COMP输出极性*/
    COMP1_InitStruct.negativeInput = FL_COMP_INN_SOURCE_INN1;                             /*配置COMP负端*/
    COMP1_InitStruct.positiveInput = FL_COMP_INP_SOURCE_INP1;                             /*配置COMP正端*/
    COMP1_InitStruct.digitalFilter = FL_ENABLE;                                           /*配置COMP数字滤波使能*/
    COMP1_InitStruct.digitalFilterLen = FL_COMP_OUTPUT_FILTER_WINDOW_3APBCLK;             /*配置COMP数字滤波周期*/

    FL_COMP_Init(COMP1, &COMP1_InitStruct);                                               /*COMP初始化*/
}

/**
* @brief  COMP1 Interrupt Initialization function
* @param  void
* @retval None
*/
void MF_COMP1_Interrupt_Init(void)
{
    FL_COMP_ClearFlag_Comparator1(COMP);                                                  /*清中断标志*/
    FL_COMP_EnableIT_Comparator1(COMP);                                                   /*配置COMP中断*/
}

/**
* @brief  NVIC Initialization function
* @param  void
* @retval None
*/
void MF_NVIC_Init(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 0x00;                                         /*配置COMP_NVIC*/
    FL_NVIC_Init(&InterruptConfigStruct, COMPx_IRQn);
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial RCHF */
    FL_CMU_RCHF_SetFrequency(FL_CMU_RCHF_FREQUENCY_8MHZ);                                 /*配置RCHF频率*/
    FL_CMU_RCHF_Enable();                                                                 /*使能RCHF*/

    /* Initial System Clock */
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);                               /*配置FLASH等待周期*/
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);                           /*配置系统时钟*/
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);                                       /*配置AHB时钟*/
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);                                       /*配置APB时钟*/

    SystemCoreClockUpdate();
}

void MF_Config_Init(void)
{
    /* Initial COMP1 */
    MF_COMP1_Init();                                                                      /*COMP初始化*/
    MF_COMP1_Interrupt_Init();                                                            /*配置COMP中断*/

    /* Initial NVIC */
    MF_NVIC_Init();                                                                       /*配置COMP_NVIC*/
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
