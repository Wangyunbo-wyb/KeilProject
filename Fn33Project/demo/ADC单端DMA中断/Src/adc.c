#include "adc.h"

volatile uint8_t ADCComplete = 0;
void DMA_IRQHandler(void)
{
    uint32_t IE_Flag, IF_Flag;
    IE_Flag = FL_DMA_IsEnabledIT_TransferComplete(DMA, FL_DMA_CHANNEL_0);             //获取中断使能以及中断标志状态
    IF_Flag = FL_DMA_IsActiveFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);
    if((0x01U == IE_Flag) && (0x01U == IF_Flag))
    {
        FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);                     //清标志
        ADCComplete = 1;

    }

}
static void ADC_DMA_Common_Init(void)
{
    FL_DMA_InitTypeDef DMA_InitStruct = {0};
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;

    DMA_InitStruct.periphAddress = FL_DMA_PERIPHERAL_FUNCTION1;                       //配置DMA通道功能
    DMA_InitStruct.direction = FL_DMA_DIR_PERIPHERAL_TO_RAM;                          //配置DMA通道方向
    DMA_InitStruct.memoryAddressIncMode = FL_DMA_MEMORY_INC_MODE_INCREASE;            //配置RAM的增减方向
    DMA_InitStruct.dataSize = FL_DMA_BANDWIDTH_16B;                                   //配置DMA传输位宽
    DMA_InitStruct.priority = FL_DMA_PRIORITY_HIGH;                                   //配置DMA通道优先级
    DMA_InitStruct.circMode = FL_DISABLE;                                             //配置DMA通道循环缓存
    (void)FL_DMA_Init(DMA, &DMA_InitStruct, FL_DMA_CHANNEL_0);

    FL_DMA_Enable(DMA);                                                               //配置DMA全局开关


    FL_DMA_ClearFlag_TransferComplete(DMA, FL_DMA_CHANNEL_0);                         //清标志
    FL_DMA_EnableIT_TransferComplete(DMA, FL_DMA_CHANNEL_0);                          //配置DMA全程中断


    InterruptConfigStruct.preemptPriority = 2U;                                       //配置DMA的优先级
    FL_NVIC_Init(&InterruptConfigStruct, DMA_IRQn);
}

void ADC_DMA_Config(uint16_t *buffer, uint32_t length)
{
    FL_DMA_ConfigTypeDef DMA_ConfigStruct = {0};
    DMA_ConfigStruct.memoryAddress = (uint32_t)buffer;                                //配置DMA_RAM地址
    DMA_ConfigStruct.transmissionCount = length - 1;                                  //配置DMA传输长度
    (void)FL_DMA_StartTransmission(DMA, &DMA_ConfigStruct, FL_DMA_CHANNEL_0);

}

uint16_t DMAResult[2];
void ADC_Config(void)
{
    FL_VREF_EnableVREFBuffer(VREF);                                                    //使能VREF BUFFER,
    //为了考虑功耗BUFFER可关闭，从使能到ADC可以正常采样需要100us的建立时间，本例程配置慢速通道较长的采样时间，来保证建立时间满足。
    ADC_DMA_Common_Init();                                                             //DMA基础初始化配置
    ADC_DMA_Config(DMAResult, 2);                                                      //DMA初始化配置

    FL_ADC_ClearFlag_EndOfConversion(ADC);                                             //清标志
    FL_ADC_Enable(ADC);                                                                //启动ADC
    FL_ADC_EnableSWConversion(ADC);                                                    //开始转换

}
uint32_t GetSingleChannelVoltage_DMA(void)
{
    uint32_t GetChannelVoltage = 0;

    if(DMAResult[1] != 0)
    {
        GetChannelVoltage = (uint32_t)(((uint64_t)DMAResult[0] * ADC_VREF * 3000) / ((uint64_t)DMAResult[1] * 4095));
    }

    return GetChannelVoltage;
}
