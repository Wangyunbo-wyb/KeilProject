#include "adc.h"

volatile uint8_t ADCComplete = 0U;
static uint32_t ExChannelSample = 0U;
static uint32_t VREF1P2ChannelSample = 0U;
static uint8_t ChannelCount0 = 0U;
void ADC_IRQHandler(void)
{
    uint32_t IE_Flag, IF_Flag;
    IE_Flag = FL_ADC_IsEnabledIT_EndOfConversion(ADC);                      //获取中断使能以及中断标志状态
    IF_Flag = FL_ADC_IsActiveFlag_EndOfConversion(ADC);

    if((0x01U == IE_Flag) && (0x01U == IF_Flag))
    {
        FL_ADC_ClearFlag_EndOfConversion(ADC);                              //清标志
        ChannelCount0++;
        if(ChannelCount0 == 1U)
        {
            ExChannelSample = FL_ADC_ReadConversionData(ADC);                 //获取采样值

        }
        else
        {
            VREF1P2ChannelSample = FL_ADC_ReadConversionData(ADC);            //获取采样值
            ChannelCount0 = 0U;
            ADCComplete = 1U;
        }

    }

}

void ADC_Config(void)
{
    FL_VREF_EnableVREFBuffer(VREF);                                         //使能VREF BUFFER,
    //为了考虑功耗BUFFER可关闭，从使能到ADC可以正常采样需要100us的建立时间，本例程配置慢速通道较长的采样时间，来保证建立时间满足。
    FL_ADC_Enable(ADC);                                                     //启动ADC
    FL_ADC_EnableSWConversion(ADC);                                         //开始转换

}

uint32_t GetSingleChannelVoltage_IT(void)
{
    uint32_t GetChannelVoltage = 0;

    if(VREF1P2ChannelSample != 0)
    {
        GetChannelVoltage = (uint32_t)(((uint64_t)ExChannelSample * 3000 * (ADC_VREF)) / ((uint64_t)VREF1P2ChannelSample * 4095));
    }

    // 转换结果
    return GetChannelVoltage;
}
