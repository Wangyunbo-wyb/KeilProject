#include "main.h"
#include "I2C.h"

int main(void)
{
    /* Configure the system clock */
    MF_Clock_Init();

    /* Initialize FL Driver Library */
    FL_Init();

    /* Initialize all configured peripherals */
    MF_Config_Init();

    while(1)
    {

    }
}


