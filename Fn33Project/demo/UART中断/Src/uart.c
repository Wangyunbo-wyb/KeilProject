#include "main.h"
#include "uart.h"
struct UARTOpStruct
{
    uint8_t *TxBuf; //发送数据指针
    uint8_t TxLen;  //待发送数据长度
    uint8_t TxOpc;  //已发送数据长度
    uint8_t *RxBuf; //接收数据指针
    uint8_t RxLen;  //待接收数据长度
    uint8_t RxOpc;  //已接收数据长度
};
struct UARTOpStruct UARTxOp;

uint8_t tmp08;
void UART0_IRQHandler(void)
{
    uint32_t UART0RXBuffFullIT = 0;
    uint32_t UART0RXBuffFullFlag = 0;
    uint32_t UART0TXBuffFullIT = 0;
    uint32_t UART0TXBuffFullFlag = 0;

    UART0RXBuffFullIT = FL_UART_IsEnabledIT_RXBuffFull(UART0);
    UART0RXBuffFullFlag = FL_UART_IsActiveFlag_RXBuffFull(UART0);
    UART0TXBuffFullIT = FL_UART_IsEnabledIT_TXShiftBuffEmpty(UART0);
    UART0TXBuffFullFlag = FL_UART_IsActiveFlag_TXShiftBuffEmpty(UART0);

    //接收中断处理
    if((UART0RXBuffFullIT == 0x01UL) && (UART0RXBuffFullFlag == 0x01UL))
    {
        //中断接收
        tmp08 = FL_UART_ReadRXBuff(UART0);     //接收中断标志可通过读取rxreg寄存器清除
    }

    //发送中断处理
    if((UART0TXBuffFullIT == 0x01UL) && (UART0TXBuffFullFlag == 0x01UL))
    {
        //发送中断标志可通过写txreg寄存器清除或txif写1清除
        //发送指定长度的数据
        if(UARTxOp.TxOpc < UARTxOp.TxLen)
        {
            FL_UART_WriteTXBuff(UART0, UARTxOp.TxBuf[UARTxOp.TxOpc]); //发送一个数据
            UARTxOp.TxOpc++;
        }

        FL_UART_ClearFlag_TXShiftBuffEmpty(UART0);  //清除发送中断标志

        if(UARTxOp.TxOpc == UARTxOp.TxLen)
        {
            FL_UART_DisableIT_TXShiftBuffEmpty(UART0);
        }
    }
}

uint8_t TestTxData[11] = "TestUart-TX";

void UartxIRQ(UART_Type *UARTx)
{
    //中断发送数组
    UARTxOp.TxBuf = TestTxData;
    UARTxOp.TxLen = 11;
    UARTxOp.TxOpc = 0 + 1;

    FL_UART_WriteTXBuff(UARTx, UARTxOp.TxBuf[0]);

}

