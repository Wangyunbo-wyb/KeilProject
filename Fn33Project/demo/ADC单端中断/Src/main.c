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
    while(1)
    {
        if(ADCComplete == 0x01U)
        {
            ADCComplete = 0;
            GetVoltage = GetSingleChannelVoltage_IT();
            FL_ADC_EnableSWConversion(ADC);
        }
    }
}


