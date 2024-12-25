#include "main.h"
#include "clock.h"

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();

    ClockInit(FL_CMU_RCHF_FREQUENCY_16MHZ);

    while(1)
    {

    }
}




