#include "main.h"
#include "wkup_interrupt.h"

//引脚中断
void NMI_Handler(void)
{
    //NWKUP默认连接到了cpu的NMI不可屏蔽中断，不受NVIC控制，不受全局中断使能控制，唤醒后必然进NMI中断
    if(FL_SET == FL_PMU_IsActiveFlag_WakeupPIN(PMU, FL_PMU_WAKEUP4_PIN))
    {
        FL_PMU_ClearFlag_WakeupPIN(PMU, FL_PMU_WAKEUP4_PIN);
    }
}


// 外部引脚中断初始化
void WKUP_Interrupt_Init(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    //用到的GPIO引脚    设为输入
    GPIO_InitStruct.pin          = FL_GPIO_PIN_6;
    GPIO_InitStruct.mode         = FL_GPIO_MODE_INPUT;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull         = FL_DISABLE;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    (void)FL_GPIO_Init(GPIOC, &GPIO_InitStruct);


    //WKUP 使能
    FL_GPIO_SetWakeupInterruptEntry(GPIO, FL_GPIO_WAKEUP_INT_ENTRY_NMI);//NMI中断入口
    FL_GPIO_SetWakeupEdge(GPIO, FL_GPIO_WAKEUP_4, FL_GPIO_WAKEUP_TRIGGER_FALLING);//下降沿唤醒
    FL_GPIO_EnableWakeup(GPIO, FL_GPIO_WAKEUP_4);//使能NWKUP功能
}
