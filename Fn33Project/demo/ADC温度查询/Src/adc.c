#include "adc.h"


static uint8_t GetVREF1P2Sample_POLL(uint32_t *ADCRdresult)
{
    uint32_t counter = 0;
    uint32_t EOC_Flag;
    uint8_t State;
    FL_CMU_SetADCPrescaler(FL_CMU_ADC_PSC_DIV8);                    //配置ADC工作时钟分频
    FL_VREF_EnableVREFBuffer(VREF);                                 //使能VREF BUFFER,
    //为了考虑功耗BUFFER可关闭，从使能到ADC可以正常采样需要100us的建立时间，本例程配置慢速通道较长的采样时间，来保证建立时间满足。
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL);        //清空打开的通道
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2);    //通道选择

    FL_ADC_ClearFlag_EndOfConversion(ADC);                          //清标志
    FL_ADC_Enable(ADC);                                             //启动ADC
    FL_ADC_EnableSWConversion(ADC);                                 //开始转换

    do
    {
        EOC_Flag = FL_ADC_IsActiveFlag_EndOfConversion(ADC);
        counter++;
    } while((counter != 0xFFFFFFFFU) && (EOC_Flag == 0U));           //等待转换完成

    if(EOC_Flag == 0x01U)
    {
        FL_ADC_ClearFlag_EndOfConversion(ADC);                        //清标志
        *ADCRdresult = FL_ADC_ReadConversionData(ADC);                 //获取采样值

        FL_ADC_Disable(ADC);                                          //关闭ADC
        FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_VREF1P2); //通道关闭
        FL_VREF_DisableVREFBuffer(VREF);                              //关闭VREF BUFFER
        State = 0;
    }
    else
    {
        State = 1 ;
    }

    return State;
}


static uint8_t GetTSSample_POLL(uint32_t *ADCRdresult)
{
    uint32_t counter = 0;
    uint32_t EOC_Flag;
    uint8_t State;

    FL_CMU_SetADCPrescaler(FL_CMU_ADC_PSC_DIV8);                  //配置ADC工作时钟分频
    FL_VREF_EnableVPTATBuffer(VREF);                              //使能PTATBUFFER
    //为了考虑功耗BUFFER可关闭，从使能到ADC可以正常采样需要100us的建立时间，本例程配置慢速通道较长的采样时间，来保证建立时间满足。
    FL_ADC_DisableSequencerChannel(ADC, FL_ADC_ALL_CHANNEL);      //清空打开的通道
    FL_ADC_EnableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);       //通道选择

    FL_ADC_ClearFlag_EndOfConversion(ADC);                        //清标志
    FL_ADC_Enable(ADC);                                           //启动ADC
    FL_ADC_EnableSWConversion(ADC);                               //开始转换

    do
    {
        EOC_Flag = FL_ADC_IsActiveFlag_EndOfConversion(ADC);
        counter++;
    } while((counter != 0xFFFFFFFFU) && (EOC_Flag == 0U));         //等待转换完成

    if(EOC_Flag == 0x01U)
    {
        FL_ADC_ClearFlag_EndOfConversion(ADC);                      //清标志
        *ADCRdresult = FL_ADC_ReadConversionData(ADC);               //获取采样值

        FL_ADC_Disable(ADC);                                        //关闭ADC
        FL_ADC_DisableSequencerChannel(ADC, FL_ADC_INTERNAL_TS);    //通道关闭
        State = 0;
    }
    else
    {
        State = 1 ;
    }

    return State;
}

float GetTS_POLL(void)
{
    uint32_t VPTAT = 0, VPTAT_30 = 0, GetTSSample = 0, GetVREF1P2Sample = 0;
    uint8_t  Get122VSample_State, GetTSample_State;
    float GetTS = 0.00f;

    Get122VSample_State = GetVREF1P2Sample_POLL(&GetVREF1P2Sample);
    GetTSample_State = GetTSSample_POLL(&GetTSSample);

    if((GetVREF1P2Sample != 0) && (Get122VSample_State == 0)  && (GetTSample_State == 0))
    {
        VPTAT = (uint32_t)(((uint64_t)GetTSSample * 3000 * (ADC_VREF)) / ((uint64_t)GetVREF1P2Sample * 4095));
        VPTAT_30 = ((uint32_t)ADC_TS * 3000) / (4095);
        GetTS = ((float)VPTAT - (float)VPTAT_30) / (2.6f) + (30.0f);
    }
    // 转换结果
    return GetTS;
}

