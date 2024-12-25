/********************************程序逻辑***************************************/
/*1、ADC――PC9配置为ADC通道******************************************************/
/*2、GPIO――PC6配置为下降沿中断**************************************************/
/*3、定义计数信号量adcSemaphore（最大10，初值5）以及二值信号量gpioSemaphore*****/
/*4、创建3个任务，分别为LedTask、AdcTask、GPIOTask******************************/
/*5、GPIO中断会释放adcSemaphore、gpioSemaphore信号量为任务获取******************/
/********************************************************************************/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "adc.h"
#include "taskadc.h"
#include "gpio.h"
#include "taskgpio.h"
#include "uart.h"

QueueHandle_t       adcSemaphore = NULL;
SemaphoreHandle_t   gpioSemaphore = NULL;

#define TASK_LED_PRIORITY       (tskIDLE_PRIORITY + 1)
#define TASK_ADC_PRIORITY       (tskIDLE_PRIORITY + 1)
#define TASK_GPIO_PRIORITY      (tskIDLE_PRIORITY + 2)

void LedTask(void *pvParameters)
{
    pvParameters = pvParameters;
    while(1)
    {
        vTaskDelay(1000);
        FL_GPIO_ToggleOutputPin(GPIOC, FL_GPIO_PIN_0);
    }
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
    DebugInit();
    printf("Debug_Init:OK\r\n");


    ADC_Init();
    GPIO_interrupt_init();

    adcSemaphore = xSemaphoreCreateCounting(10, 5);
    gpioSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(LedTask, "Led", configMINIMAL_STACK_SIZE, NULL, TASK_LED_PRIORITY, NULL);
    xTaskCreate(AdcTask, "Adc", configMINIMAL_STACK_SIZE, NULL, TASK_ADC_PRIORITY, NULL);
    xTaskCreate(GPIOTask, "GPIO", configMINIMAL_STACK_SIZE, NULL, TASK_GPIO_PRIORITY, NULL);

    vTaskStartScheduler();
    while(1)
    {

    }
}


