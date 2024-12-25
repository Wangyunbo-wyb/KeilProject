#include "demo_lpuart.h"

uint8_t temp = 0;
//LPUARTx 中断处理函数
void LPUARTx_IRQHandler(void)
{
    //LPUART0接收中断处理
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART0))
            && (FL_SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0)))      //接收数据中断
    {
        temp = FL_LPUART_ReadRXBuff(LPUART0);                               //接收数据
    }

    //LPUART0发送中断处理
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART0))
            && (FL_SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART0)))
    {
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART0);                      //清除发送中断标志
        /* 用户代码*/
    }

    //LPUART1接收中断处理
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART1))
            && (FL_SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART1)))      //接收数据中断
    {
        temp = FL_LPUART_ReadRXBuff(LPUART1);                               //接收数据
    }

    //LPUART1发送中断处理
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART1))
            && (FL_SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART1)))
    {
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART1);                      //清除发送中断标志
        /* 用户代码*/
    }



    //LPUART2接收中断处理
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_RXBuffFull(LPUART2))
            && (FL_SET == FL_LPUART_IsActiveFlag_RXBuffFull(LPUART2)))      //接收数据中断
    {
        temp = FL_LPUART_ReadRXBuff(LPUART2);                               //接收数据
    }

    //LPUART2发送中断处理
    if((FL_ENABLE == FL_LPUART_IsEnabledIT_TXShiftBuffEmpty(LPUART2))
            && (FL_SET == FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART2)))
    {
        FL_LPUART_ClearFlag_TXShiftBuffEmpty(LPUART2);                     //清除发送中断标志
        /* 用户代码*/
    }

}

//LPUART0 查询收发程序,收一个字节,立即将这个字节发送出去
void LPUART0_Query(void)
{
    uint8_t temp;
    uint32_t counter;
    uint32_t status;
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART0))                        //等待接收到一个字节
    {
        temp = FL_LPUART_ReadRXBuff(LPUART0);                             //LPUART接收数据
        FL_LPUART_ClearFlag_RXBuffFull(LPUART0);
        FL_LPUART_WriteTXBuff(LPUART0, temp);                             //将发送数据写入发送寄存器
        counter = 0;
        do
        {
            status = FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART0);      //移位寄存器状态
            counter++;
        } while((counter != 0xffffffff) && (status != 0x01));            //超时或移位寄存器是否空 则跳出
    }
}

//LPUART1 查询收发程序,收一个字节,立即将这个字节发送出去
void LPUART1_Query(void)
{
    uint8_t temp;
    uint32_t counter;
    uint32_t status;
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART1))                        //等待接收到一个字节
    {
        temp = FL_LPUART_ReadRXBuff(LPUART1);                             //LPUART接收数据
        FL_LPUART_ClearFlag_RXBuffFull(LPUART1);
        FL_LPUART_WriteTXBuff(LPUART1, temp);                             //将发送数据写入发送寄存器
        counter = 0;
        do
        {
            status = FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART1);      //移位寄存器状态
            counter++;
        } while((counter != 0xffffffff) && (status != 0x01));            //超时或移位寄存器是否空 则跳出
    }
}

//LPUART2 查询收发程序,收一个字节,立即将这个字节发送出去
void LPUART2_Query(void)
{
    uint8_t temp;
    uint32_t counter;
    uint32_t status;
    if(FL_LPUART_IsActiveFlag_RXBuffFull(LPUART2))                        //等待接收到一个字节
    {
        temp = FL_LPUART_ReadRXBuff(LPUART2);                             //LPUART接收数据
        FL_LPUART_ClearFlag_RXBuffFull(LPUART2);
        FL_LPUART_WriteTXBuff(LPUART2, temp);                             //将发送数据写入发送寄存器
        counter = 0;
        do
        {
            status = FL_LPUART_IsActiveFlag_TXShiftBuffEmpty(LPUART2);      //移位寄存器状态
            counter++;
        } while((counter != 0xffffffff) && (status != 0x01));            //超时或移位寄存器是否空 则跳出
    }
}



