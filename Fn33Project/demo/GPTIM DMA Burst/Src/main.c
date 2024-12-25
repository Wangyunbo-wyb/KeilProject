#include "main.h"
#include "gptim_dmaburst_pwm.h"

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

    GPTIM_Setup();

    while(1)
    {
        GPTIM_Loop();
    }
}


