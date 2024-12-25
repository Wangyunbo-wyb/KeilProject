#include "main.h"
#include "uart.h"

void UartxInfraredTransmit(UART_Type *UARTx)
{
    uint8_t TestTxData[11] = "TestUart-TX";
    uint8_t i;


    //查询发送数组
    for(i = 0; i < 11; i++)
    {
        FL_UART_WriteTXBuff(UARTx, TestTxData[i]);                //将发送数据写入发送寄存器
        while(0x01UL != FL_UART_IsActiveFlag_TXBuffEmpty(UARTx)); //等待发送完成
    }
}

