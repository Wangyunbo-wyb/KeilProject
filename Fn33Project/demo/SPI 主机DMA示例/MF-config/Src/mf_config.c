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
  * @brief  DMA_Channel5 Initialization function
  * @param  void
  * @retval None
  */
void MF_DMA_Channel5_Init(void)
{
    FL_DMA_InitTypeDef    DMA_InitStruct;

    DMA_InitStruct.circMode = FL_DISABLE;
    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
    DMA_InitStruct.direction = FL_DMA_DIR_PERIPHERAL_TO_RAM;
    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION1;
    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
    DMA_InitStruct.flashAddressIncMode = FL_DMA_CH7_FLASH_INC_MODE_INCREASE;

    FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_5);
}

/**
  * @brief  DMA_Channel6 Initialization function
  * @param  void
  * @retval None
  */
void MF_DMA_Channel6_Init(void)
{
    FL_DMA_InitTypeDef    DMA_InitStruct;

    DMA_InitStruct.circMode = FL_DISABLE;
    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
    DMA_InitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;
    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION1;
    DMA_InitStruct.priority = FL_DMA_PRIORITY_MEDIUM;
    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
    DMA_InitStruct.flashAddressIncMode = FL_DMA_CH7_FLASH_INC_MODE_INCREASE;

    FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_6);
}

/**
  * @brief  SPI1 Initialization function
  * @param  void
  * @retval None
  */
void MF_SPI1_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;

    FL_SPI_InitTypeDef    SPI1_InitStruct;

    GPIO_InitStruct.pin = FL_GPIO_PIN_8;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.pin = FL_GPIO_PIN_9;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.pin = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.pin = FL_GPIO_PIN_1;
    GPIO_InitStruct.mode = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    SPI1_InitStruct.softControl = FL_DISABLE;
    SPI1_InitStruct.mode = FL_SPI_WORK_MODE_MASTER;
    SPI1_InitStruct.baudRate = FL_SPI_BAUDRATE_DIV8;
    SPI1_InitStruct.bitOrder = FL_SPI_BIT_ORDER_MSB_FIRST;
    SPI1_InitStruct.dataWidth = FL_SPI_DATA_WIDTH_8B;
    SPI1_InitStruct.clockPhase = FL_SPI_PHASE_EDGE2;
    SPI1_InitStruct.transferMode = FL_SPI_TRANSFER_MODE_FULL_DUPLEX;
    SPI1_InitStruct.clockPolarity = FL_SPI_POLARITY_NORMAL;

    FL_SPI_Init(SPI1, &SPI1_InitStruct);
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
    FL_NVIC_Init(&InterruptConfigStruct, DMA_IRQn);
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
    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_0CYCLE);    /* 设置FLASH读等待为 0 个周期 */
    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_RCHF);    /* 设置系统主时钟为 RCHF */
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);

    SystemCoreClockUpdate();
}

void MF_Config_Init(void)
{
    /* Initial DMA */
    MF_DMA_Channel5_Init();
    MF_DMA_Channel6_Init();

    /* Initial SPI1 */
    MF_SPI1_Init();

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
