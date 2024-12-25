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
  * @brief  LPUART0 Initialization function
  * @param  void
  * @retval None
  */
void MF_LPUART0_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_LPUART_InitTypeDef    LPUART0_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_13;                                                 /*配置GPIO的引脚号*/
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;                                          /*配置GPIO的功能模式*/
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;                                 /*配置GPIO的输出模式*/
    GPIO_InitStruct.pull = FL_DISABLE;                                                    /*配置GPIO输上拉模式*/
    GPIO_InitStruct.remapPin = FL_ENABLE;                                                 /*配置GPIO数字重定向功能*/
    GPIO_InitStruct.analogSwitch = FL_DISABLE;                                            /*配置GPIO模拟开关功能*/
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);                                                /*GPIO初始化*/

    GPIO_InitStruct.pin = FL_GPIO_PIN_14;                                                 /*配置GPIO的引脚号*/
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;                                          /*配置GPIO的功能模式*/
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;                                 /*配置GPIO的输出模式*/
    GPIO_InitStruct.pull = FL_DISABLE;                                                    /*配置GPIO输上拉模式*/
    GPIO_InitStruct.remapPin = FL_ENABLE;                                                 /*配置GPIO数字重定向功能*/
    GPIO_InitStruct.analogSwitch = FL_DISABLE;                                            /*配置GPIO模拟开关功能*/
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);                                                /*GPIO初始化*/

    LPUART0_InitStruct.baudRate = FL_LPUART_BAUDRATE_9600;                                /*配置LPUART波特率*/
    LPUART0_InitStruct.dataWidth = FL_LPUART_DATA_WIDTH_8B;                               /*配置LPUART数据位数*/
    LPUART0_InitStruct.stopBits = FL_LPUART_STOP_BIT_WIDTH_1B;                            /*配置LPUART数据停止位*/
    LPUART0_InitStruct.parity = FL_LPUART_PARITY_NONE;                                    /*配置LPUART数据奇偶检验位*/
    LPUART0_InitStruct.transferDirection = FL_LPUART_DIRECTION_NONE;                      /*配置LPUART发送、接收使能*/
    LPUART0_InitStruct.clockSrc = FL_CMU_LPUART_CLK_SOURCE_LSCLK;                         /*配置LPUART工作时钟*/

    FL_LPUART_Init(LPUART0, &LPUART0_InitStruct);                                         /*LPUART初始化*/
}

/**
  * @brief  LPUART0 Interrupt Initialization function
  * @param  void
  * @retval None
  */
void MF_LPUART0_Interrupt_Init(void)
{
    FL_LPUART_ClearFlag_RXBuffFull(LPUART0);                                              /*配置LPUART中断*/
    FL_LPUART_EnableIT_RXBuffFull(LPUART0);

    FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART0);
    FL_LPUART_EnableIT_TXShiftBuffEmpty(LPUART0);
}

/**
  * @brief  NVIC Initialization function
  * @param  void
  * @retval None
  */
void MF_NVIC_Init(void)
{
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    InterruptConfigStruct.preemptPriority = 0x02;                                         /*配置LPUART_NVIC*/
    FL_NVIC_Init(&InterruptConfigStruct, LPUARTx_IRQn);
}


/**
  * @brief  Clock Initialization.
  * @retval None
  */
void MF_Clock_Init(void)
{
    /* Initial XTLF */
    FL_CDIF_EnableCPUToVAO(CDIF);                                                         /*使能跨电源域接口*/
    FL_VAO_XTLF_Disable(VAO);                                                             /*禁止XTLF*/
    FL_CDIF_DisableCPUToVAO(CDIF);                                                        /*禁止跨电源域接口*/

    /* Initial Low Speed Clock */
    FL_CMU_SetLSCLKClockSource(FL_CMU_LSCLK_CLK_SOURCE_RCLP);                             /*配置LSCLK时钟源*/

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
    /* Initial LPUART0 */
    MF_LPUART0_Init();                                                                    /*LPUART初始化*/
    MF_LPUART0_Interrupt_Init();                                                          /*配置LPUART中断*/

    /* Initial NVIC */
    MF_NVIC_Init();                                                                       /*配置LPUART_NVIC*/
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
