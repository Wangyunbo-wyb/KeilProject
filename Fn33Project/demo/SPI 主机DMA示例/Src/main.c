#include "main.h"
#include "spi_master_dma.h"

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

    SPI_DMARW_Setup();

    while(1)
    {
        SPI_DMARW_Loop();
        FL_DelayMs(1000);
    }
}


