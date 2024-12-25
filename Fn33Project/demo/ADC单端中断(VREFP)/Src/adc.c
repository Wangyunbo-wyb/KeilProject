#include "adc.h"

volatile uint8_t ADCComplete = 0U;
static uint32_t ExChannelSample = 0U;
void ADC_IRQHandler(void)
{
    uint32_t IE_Flag, IF_Flag;
    IE_Flag = FL_ADC_IsEnabledIT_EndOfConversion(ADC);                      //获取中断使能以及中断标志状态
    IF_Flag = FL_ADC_IsActiveFlag_EndOfConversion(ADC);

    if((0x01U == IE_Flag) && (0x01U == IF_Flag))
    {
        FL_ADC_ClearFlag_EndOfConversion(ADC);                              //清标志

        ExChannelSample = FL_ADC_ReadConversionData(ADC);                 //获取采样值

        ADCComplete = 1U;
    }

}

void ADC_Config(void)
{
    FL_ADC_Enable(ADC);                                                     //启动ADC
    FL_ADC_EnableSWConversion(ADC);                                         //开始转换

}

uint32_t GetSingleChannelVoltage_IT(void)
{
    uint32_t GetChannelVoltage = 0;

    GetChannelVoltage = (uint32_t)((ExChannelSample * 3000) / 4095);

    // 转换结果
    return GetChannelVoltage;
}
