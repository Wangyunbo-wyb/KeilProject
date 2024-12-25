#include "gpio.h"
#include "taskgpio.h"
void GPIO_IRQHandler(void)
{
    if(FL_GPIO_IsActiveFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_9))
    {
        FL_GPIO_ClearFlag_EXTI(GPIO, FL_GPIO_EXTI_LINE_9);
        GPIO_IRQCallBack();
    }
}

void GPIO_interrupt_init(void)
{
    FL_GPIO_InitTypeDef gpioInitStruct = {0};
    FL_EXTI_InitTypeDef extiInitStruct = {0};
    FL_EXTI_CommonInitTypeDef  extiCommonInitStruct = {0};

    FL_CMU_EnableEXTIOnSleep();//休眠使能外部中断采样

    extiCommonInitStruct.clockSource = FL_CMU_EXTI_CLK_SOURCE_HCLK;    //EXTI中断采样时钟选择
    FL_EXTI_CommonInit(&extiCommonInitStruct);

    //用到的GPIO引脚    设为输入
    gpioInitStruct.pin        = FL_GPIO_PIN_6;
    gpioInitStruct.mode       = FL_GPIO_MODE_INPUT;
    gpioInitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    gpioInitStruct.pull       = FL_DISABLE;
    gpioInitStruct.remapPin   = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &gpioInitStruct);


    extiInitStruct.input       = FL_GPIO_EXTI_INPUT_GROUP2;          //中断线上对应的IO
    extiInitStruct.filter      = FL_ENABLE;                          //使能数字滤波
    extiInitStruct.triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;   //设置触发边沿
    (void)FL_EXTI_Init(FL_GPIO_EXTI_LINE_9, &extiInitStruct);


    /*NVIC中断配置*/
    NVIC_DisableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn, 2); //中断优先级配置
    NVIC_EnableIRQ(GPIO_IRQn);
}
