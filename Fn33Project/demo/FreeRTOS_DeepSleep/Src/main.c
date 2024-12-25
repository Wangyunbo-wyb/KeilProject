#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Tickless_Hook.h"
#include "lptim32_timing.h"
#include "semphr.h"
#include "gpio.h"
#include "taskgpio.h"


SemaphoreHandle_t   gpioSemaphore = NULL;
#define TASK_GPIO_PRIORITY          (tskIDLE_PRIORITY + 2)



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

    FL_DelayMs(3000);//32768 起振时间典型时间1S，最大3S
    FL_CDIF_EnableVAOToCPU(CDIF);//32768信号从VAO传输到CPU

    GPIO_interrupt_init();
    LPTIM32_Init();

    gpioSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(GPIOTask, "GPIO", configMINIMAL_STACK_SIZE, NULL, TASK_GPIO_PRIORITY, NULL);

    vTaskStartScheduler();
    while(1)
    {

    }
}


