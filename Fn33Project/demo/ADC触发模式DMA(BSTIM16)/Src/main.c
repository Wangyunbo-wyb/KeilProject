#include "main.h"
#include "adc.h"
uint32_t  GetVoltage;

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();


    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();

    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();

    ADC_Config();
    FL_BSTIM16_Enable(BSTIM16);
    while(1)
    {
        if(ADCComplete == 0x01U)
        {
            ADCComplete = 0;
            GetVoltage = GetSingleChannelVoltage_DMA();
            ADC_DMA_Config(DMAResult, 2);
            FL_ADC_ClearFlag_EndOfConversion(ADC);
            FL_ADC_Enable(ADC);
        }
    }
}




