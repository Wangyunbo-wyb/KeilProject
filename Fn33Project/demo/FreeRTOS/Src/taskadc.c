#include "taskadc.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "adc.h"
#include "task.h"

extern QueueHandle_t   adcSemaphore;
uint32_t ADC_V;

void AdcTask(void *pvParameters)
{
    pvParameters = pvParameters;

    while(1)
    {

        if(xSemaphoreTake(adcSemaphore, portMAX_DELAY) == pdPASS)
        {
            ADC_V = GetSingleChannelVoltage_POLL(FL_ADC_EXTERNAL_CH1);
            printf("CONVERT: %dmv\r\n", ADC_V);

        }
        vTaskDelay(1000);
    }
}
