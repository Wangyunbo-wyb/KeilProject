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
  * @brief  ADC_Common Initialization function
  * @param  void
  * @retval None
  */
static void MF_ADC_Common_Init(void)
{
    FL_ADC_CommonInitTypeDef    Common_InitStruct;

    Common_InitStruct.clockSource = FL_CMU_ADC_CLK_SOURCE_RCHF;                         /*配置ADC工作时钟源*/
    Common_InitStruct.clockPrescaler = FL_ADC_CLK_PSC_DIV8;                             /*配置ADC工作时钟分配*/
    Common_InitStruct.referenceSource = FL_ADC_REF_SOURCE_VDDA;                         /*配置ADC参考源*/
    Common_InitStruct.bitWidth = FL_ADC_BIT_WIDTH_12B;                                  /*配置ADC输出位宽*/

    (void)FL_ADC_CommonInit(&Common_InitStruct);
}

/**
  * @brief  ADC Initialization function
  * @param  void
  * @retval None
  */
static void MF_ADC_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_ADC_InitTypeDef    ADC_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_1;                                                /*配置GPIO的引脚号*/
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;                                         /*配置GPIO的功能模式*/
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;                               /*配置GPIO的输出模式*/
    GPIO_InitStruct.pull = FL_DISABLE;                                                  /*配置GPIO输上拉模式*/
    GPIO_InitStruct.remapPin = FL_DISABLE;                                              /*配置GPIO数字重定向功能*/
    GPIO_InitStruct.analogSwitch = FL_DISABLE;                                          /*配置GPIO模拟开关功能*/
    (void)FL_GPIO_Init(GPIOD, &GPIO_InitStruct);                                              /*GPIO初始化*/

    ADC_InitStruct.conversionMode = FL_ADC_CONV_MODE_SINGLE;                            /*配置ADC转换模式*/
    ADC_InitStruct.autoMode = FL_ADC_SINGLE_CONV_MODE_AUTO;                             /*配置ADC转换流程，仅对单次转换有效*/
    ADC_InitStruct.waitMode = FL_ENABLE;                                                /*配置ADC等待模式*/
    ADC_InitStruct.overrunMode = FL_ENABLE;                                             /*配置ADC_Overrun模式*/
    ADC_InitStruct.scanDirection = FL_ADC_SEQ_SCAN_DIR_FORWARD;                         /*配置ADC扫描顺序*/
    ADC_InitStruct.externalTrigConv = FL_ADC_TRIGGER_EDGE_NONE;                         /*配置非软件触发使能及极性*/
    ADC_InitStruct.triggerSource = FL_DISABLE;                                          /*配置ADC非软件触发源*/
    ADC_InitStruct.fastChannelTime = FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK;             /*配置ADC快速通道采样时间*/
    ADC_InitStruct.lowChannelTime = FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK;            /*配置ADC慢速通道采样时间*/
    ADC_InitStruct.oversamplingMode = FL_DISABLE;                                       /*配置ADC过采样模式*/
    ADC_InitStruct.overSampingMultiplier = FL_ADC_OVERSAMPLING_MUL_16X;                 /*配置ADC过采样率*/
    ADC_InitStruct.oversamplingShift = FL_ADC_OVERSAMPLING_SHIFT_4B;                    /*配置ADC过采样结果移位*/

    (void)FL_ADC_Init(ADC, &ADC_InitStruct);

    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);                        /*通道使能*/
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_EXTERNAL_CH1);
}

/**
  * @brief  ADC Interrupt Initialization function
  * @param  void
  * @retval None
  */
static void MF_ADC_Interrupt_Init(void)
{
    FL_ADC_ClearFlag_EndOfConversion(ADC);                                              /*清标志*/
    FL_ADC_EnableIT_EndOfConversion(ADC);                                               /*中断使能*/
}

/**
  * @brief  NVIC Initialization function
  * @param  void
  * @retval None
  */
static void MF_NVIC_Init(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 0x2;                                        /*配置中断优先级*/
    FL_NVIC_Init(&InterruptConfigStruct, ADC_IRQn);
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
    /* Initial ADC */
    MF_ADC_Common_Init();                                                               /*ADC基础配置*/
    MF_ADC_Init();                                                                      /*ADC初始化配置*/
    MF_ADC_Interrupt_Init();                                                            /*ADC中断配置*/

    /* Initial NVIC */
    MF_NVIC_Init();                                                                     /*ADC中断优先级配置*/
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
