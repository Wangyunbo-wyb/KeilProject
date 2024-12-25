#include "main.h"
#include "adc.h"

int32_t  GetVoltage;

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

    while(1)
    {
        GetVoltage = GetDifferentialChannelVoltage_POLL(FL_ADC_DIFFERENTIAL_GROUP1);
    }
}


