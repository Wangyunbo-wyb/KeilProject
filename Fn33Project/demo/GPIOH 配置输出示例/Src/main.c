#include "main.h"

void PH15_OUTPUT_HIGH(void)
{
    FL_CDIF_EnableCPUToVAO(CDIF);

    FL_VAO_GPIO_WritePH15Output(VAO, 1);

    FL_CDIF_DisableCPUToVAO(CDIF);
}
void PH15_OUTPUT_LOW(void)
{
    FL_CDIF_EnableCPUToVAO(CDIF);

    FL_VAO_GPIO_WritePH15Output(VAO, 0);

    FL_CDIF_DisableCPUToVAO(CDIF);
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

    while(1)
    {
        PH15_OUTPUT_HIGH();
        FL_DelayMs(100);
        PH15_OUTPUT_LOW();
        FL_DelayMs(100);
    }
}


