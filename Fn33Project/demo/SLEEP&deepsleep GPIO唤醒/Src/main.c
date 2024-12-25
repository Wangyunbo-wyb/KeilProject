#include "main.h"
#include "sleep.h"
#include "gpio_interrupt.h"

uint8_t i;

void LED_Init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.pin          = FL_GPIO_PIN_0;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_DISABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    FL_GPIO_SetOutputPin(GPIOC,FL_GPIO_PIN_0);
}

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

    GPIO_Interrupt_Init();

    LED_Init();

    while(1)
    {
        DeepSleep();
        for(i = 0; i < 5; i++)
        {
            FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
            FL_DelayMs(500);
        }
    }
}


