#include "dac.h"

volatile uint8_t DACComplete = 0;
void DMA_IRQHandler(void)
{
    uint32_t IE_Flag, IF_Flag;
    IE_Flag = FL_DMA_IsEnabledIT_TransferComplete(DMA, FL_DMA_CHANNEL_1);             //获取中断使能以及中断标志状态
    IF_Flag = FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1);
    if((0x01U == IE_Flag) && (0x01U == IF_Flag))
    {
        FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1);                     //清标志
        DACComplete = 1;

    }

}
void GPIO_IRQHandler(void)
{
    uint32_t IF_Flag;
    IF_Flag = FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_0);                  //获取中断标志状态
    if(0x01U == IF_Flag)
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_0);
    }

}

static void DAC_DMA(uint16_t *buffer, uint32_t length)
{
    FL_DMA_InitTypeDef DMA_InitStruct = {0};
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;
    FL_DMA_ConfigTypeDef DMA_ConfigStruct = {0};
    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION8;                       //配置DMA通道功能
    DMA_InitStruct.direction = FL_DMA_DIR_RAM_TO_PERIPHERAL;                          //配置DMA通道方向
    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;            //配置RAM的增减方向
    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_16B;                                   //配置DMA传输位宽
    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;                                   //配置DMA通道优先级
    DMA_InitStruct.circMode = FL_DISABLE;                                             //配置DMA通道循环缓存
    (void)FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_1);                        //配置DMA初始化

    FL_DMA_Enable(DMA);                                                               //配置DMA全局开关

    DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;                                //配置DMA_RAM地址
    DMA_ConfigStruct.transmissionCount = length - 1;                                  //配置DMA传输长度
    (void)FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_1);


    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_1);                         //清标志
    FL_DMA_EnableIT_TransferComplete(DMA, FL_DMA_CHANNEL_1);                          //配置DMA全程中断


    InterruptConfigStruct.preemptPriority = 2U;                                       //配置DMA的优先级
    FL_NVIC_Init(&InterruptConfigStruct, DMA_IRQn);


}
uint16_t DACdata[2] = {2047, 1000};

void DAC_EXTTrigger(void)
{
    FL_DAC_WriteData(DAC, 4095);                                                      //配置DAC默认值
    FL_DAC_Enable(DAC);                                                               //配置DAC使能
    DAC_DMA(DACdata, 3);                                                              //配置DMA

}




