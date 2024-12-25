#include "main.h"
#include "uart.h"

uint8_t tmp08;
/*下降沿唤醒中断处理函数*/
void UART0_IRQHandler(void)
{
    uint32_t UART0RXBuffFallingEdgeWakeupIT = 0;
    uint32_t UART0RXBuffFallingEdgeWakeupFlag = 0;
    uint32_t counter = 0;
    uint32_t RXFlag = 0;
    UART0RXBuffFallingEdgeWakeupIT = FL_UART_IsEnabledIT_FallingEdgeWakeup(UART0);
    UART0RXBuffFallingEdgeWakeupFlag = FL_UART_IsActiveFlag_FallingEdgeWakeup(UART0);


    //下降沿唤醒中断处理
    if((UART0RXBuffFallingEdgeWakeupIT == 0x01UL) && (UART0RXBuffFallingEdgeWakeupFlag == 0x01UL))
    {
        FL_UART_ClearFlag_FallingEdgeWakeup(UART0);

        do
        {
            RXFlag = FL_UART_IsActiveFlag_RXBuffFull(UART0);
            counter++;
        } while((counter != 0xFFFFFFFFU) && (RXFlag == 0U));           //等待转换完成


        tmp08 = FL_UART_ReadRXBuff(UART0);                                        //uart接收中断标志可通过读取rxreg清除
    }
}

