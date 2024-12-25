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
  * @brief  DMA_Channel0 Initialization function
  * @param  void
  * @retval None
  */
void MF_DMA_Channel0_Init(void)
{
    FL_DMA_InitTypeDef    DMA_InitStruct;

    DMA_InitStruct.circMode = FL_DISABLE;
    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_8B;
    DMA_InitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;
    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION5;
    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;
    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;
    DMA_InitStruct.flashAddressIncMode = FL_DMA_CH7_FLASH_INC_MODE_INCREASE;

    FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_0);
}

/**
  * @brief  CRC Initialization function
  * @param  void
  * @retval None
  */
void MF_CRC_Init(void)
{
    FL_CRC_InitTypeDef    CRC_InitStruct;

    CRC_InitStruct.initVal = 0x00000000;
    CRC_InitStruct.polynomial = 0x00001021;
    CRC_InitStruct.polynomialWidth = FL_CRC_POLYNOMIAL_16B;
    CRC_InitStruct.dataWidth = FL_CRC_DATA_WIDTH_8B;
    CRC_InitStruct.calculatMode = FL_CRC_CALCULATE_SERIAL;
    CRC_InitStruct.reflectIn = FL_CRC_INPUT_INVERT_BYTE;
    CRC_InitStruct.reflectOut = FL_CRC_OUPUT_INVERT_BYTE;
    CRC_InitStruct.xorReg = 0x00000000;
    CRC_InitStruct.xorRegState = FL_DISABLE;

    FL_CRC_Init(CRC, &CRC_InitStruct);
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
    MF_DMA_Channel0_Init();

    /* Initial CRC */
    MF_CRC_Init();
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
