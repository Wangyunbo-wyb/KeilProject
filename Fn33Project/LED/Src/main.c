#include "main.h"
#include "fout.h"
#include "fm33lg0xx_fl_gpio.h"
// led1连接的是pc1引脚
void LED_Init()
{
    FL_GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.pin = FL_GPIO_PIN_1;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;           // 输出
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL; // 推挽
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
int main(void)
{
    LED_Init();
    while (1)
    {
        FL_GPIO_ResetOutputPin(GPIOC, FL_GPIO_PIN_1);
    }
}
