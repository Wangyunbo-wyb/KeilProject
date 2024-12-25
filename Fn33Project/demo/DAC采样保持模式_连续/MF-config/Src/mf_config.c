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
  * @brief  DAC Initialization function
  * @param  void
  * @retval None
  */
static void MF_DAC_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_DAC_InitTypeDef    DAC_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_5;                                                /*配置GPIO的引脚号*/
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;                                         /*配置GPIO的功能模式*/
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;                               /*配置GPIO的输出模式*/
    GPIO_InitStruct.pull = FL_DISABLE;                                                  /*配置GPIO输上拉模式*/
    GPIO_InitStruct.remapPin = FL_DISABLE;                                              /*配置GPIO数字重定向功能*/
    GPIO_InitStruct.analogSwitch = FL_DISABLE;                                          /*配置GPIO模拟开关功能*/
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);                                        /*GPIO初始化*/

    DAC_InitStruct.triggerMode = FL_DISABLE;                                            /*配置触发模式使能*/
    DAC_InitStruct.triggerSource = FL_DAC_TRGI_SOFTWARE;                                /*配置触发源*/
    DAC_InitStruct.sampleHoldMode = FL_ENABLE;                                          /*配置采样保持使能*/
    DAC_InitStruct.holdTime = 0x0;                                                      /*配置保持时间*/
    DAC_InitStruct.sampleTime = 0xFF;                                                   /*配置采样时间*/
    DAC_InitStruct.bufferMode = FL_ENABLE;                                              /*配置buffer模式*/
    DAC_InitStruct.switchMode = FL_ENABLE;                                              /*配置buffer反馈开关*/

    (void)FL_DAC_Init(DAC, &DAC_InitStruct);                                            /*DAC初始化*/
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
    /* Initial DAC */
    MF_DAC_Init();                                                                      /*DAC初始化配置*/
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
void assert_failed(uint8_t *file, uint32_t linetmp)
{

}
#endif /* USE_FULL_ASSERT */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
