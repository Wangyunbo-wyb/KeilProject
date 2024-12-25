#include "main.h"
#include "uart.h"

void UartxPoll(UART_Type *UARTx)
{
    uint8_t TestTxData[3] = {0x55, 0x4A, 0x01};
    uint8_t i;

    //查询发送数组
    for(i = 0; i < 3; i++)
    {
        FL_UART_WriteTXBuff(UARTx, TestTxData[i]);        //将发送数据写入发送寄存器

        while(0x01UL != FL_UART_IsActiveFlag_TXShiftBuffEmpty(UARTx)); //等待发送完成

        FL_UART_ClearFlag_TXShiftBuffEmpty(UARTx);

    }

}

