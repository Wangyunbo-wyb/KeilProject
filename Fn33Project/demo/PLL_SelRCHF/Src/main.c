#include "main.h"
#include "pll.h"
#include "fout.h"

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

    SelRCHFToPLL(FL_CMU_RCHF_FREQUENCY_8MHZ, 64 - 1);

    FoutInit();

    while(1)
    {

    }
}


