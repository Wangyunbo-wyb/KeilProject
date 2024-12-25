#include "can.h"


CanTxMsg TxMessage = {0};                //发送缓冲区
CanRxMsg RxMessage = {0};                //接收缓冲区

void CAN_IRQHandler(void)            //中断接收
{
    if((FL_ENABLE == FL_CAN_IsEnabledIT_RXOK(CAN))
            && (FL_SET == FL_CAN_IsActiveFlag_RXOK(CAN)))
    {
        FL_CAN_FIFO_Read();
        FL_CAN_ClearFlag_RXOK(CAN);
    }

}

/**
  * @brief  通过TX FIFO发送数据
  * @param  CANx
  * @retval  None
  */

void FL_CAN_FIFO_Write(uint32_t id, uint32_t len, uint32_t data1, uint32_t data2)
{
    uint32_t counter = 0;
    uint32_t buffstatus;
    //状态标志为0时，才能清0中断标志
    do
    {
        buffstatus = FL_CAN_IsActiveFlag_TXBuffFullSignal(CAN);
        counter++;
    } while((buffstatus != 0U) && (counter != CAN_TIMEOUT));

    FL_CAN_ClearFlag_TXBuffFull(CAN);
    FL_CAN_WriteTXMessageID(CAN, id);
    FL_CAN_WriteTXMessageLength(CAN, len);
    FL_CAN_WriteTXMessageWord1(CAN, data1);
    FL_CAN_WriteTXMessageWord2(CAN, data2);
}

/**
  * @brief  通过HPB发送数据
  * @param  CANx
  * @retval  None
  */

void FL_CAN_HPBUF_Write(uint32_t id, uint32_t len, uint32_t data1, uint32_t data2)
{
    uint32_t counter = 0;
    uint32_t buffstatus;
    do
    {
        buffstatus = FL_CAN_IsActiveFlag_TXHighPriorBuffFullSignal(CAN);
        counter++;
    } while((buffstatus != 0U) && (counter != CAN_TIMEOUT));

    FL_CAN_ClearFlag_TXHighPriorBuffFull(CAN);
    FL_CAN_WriteHighPriorTXMessageID(CAN, id);
    FL_CAN_WriteHighPriorMessageLength(CAN, len);
    FL_CAN_WriteHighPriorMessageWord1(CAN, data1);
    FL_CAN_WriteHighPriorMessageWord2(CAN, data2);
}


uint8_t Data[8] = {0x68, 0x34, 0x55, 0xaa, 0x67, 0x36, 0x58, 0x16}; //要发送的数据
/**
  * @brief  发送数据设置
  * @param  CANx
  * @retval  None
  */
void CAN_SetMsg(CanTxMsg *TxMessage)
{
    uint8_t ubCounter = 0;

    TxMessage->ExtId = 0X1AB55993;                   //使用扩展ID
    TxMessage->DLC = 8;                          //数据长度为8字节


    //设置要发送的数据0-7
    for(ubCounter = 0; ubCounter < 8; ubCounter++)
    {
        TxMessage->Data[ubCounter] = Data[ubCounter];
    }

}

/**
  * @brief  读RX FIFO数据
  * @param  CANx
  * @retval  None
  */



void FL_CAN_FIFO_Read(void)
{

    uint32_t data1 = 0;
    uint32_t data2 = 0;

    RxMessage.ExtId = FL_CAN_ReadRXMessageID(CAN);
    RxMessage.DLC = FL_CAN_ReadRXMessageLength(CAN);

    data1 = FL_CAN_ReadRXMessageWord1(CAN);
    data2 = FL_CAN_ReadRXMessageWord2(CAN);

    RxMessage.Data[0] = (uint8_t)(data1 & 0xffU);
    RxMessage.Data[1] = (uint8_t)((data1 >> 8) & 0xffU);
    RxMessage.Data[2] = (uint8_t)((data1 >> 16) & 0xffU);
    RxMessage.Data[3] = (uint8_t)((data1 >> 24) & 0xffU);
    RxMessage.Data[4] = (uint8_t)(data2 & 0xffU);
    RxMessage.Data[5] = (uint8_t)((data2 >> 8) & 0xffU);
    RxMessage.Data[6] = (uint8_t)((data2 >> 16) & 0xffU);
    RxMessage.Data[7] = (uint8_t)((data2 >> 24) & 0xffU);

}

/**
  * @brief  帧模式选择
  * @param  CANx
  * @retval  None
  */
void FL_CAN_Frame_Send(uint32_t frame_format, CanTxMsg *TxMessage)
{

    uint32_t id = 0;
    uint32_t len = 0;
    uint32_t data1 = 0;
    uint32_t data2 = 0;

    if(frame_format == FL_CAN_FORMAT_STANDARD_DATA) //标准数据帧
    {
        id = TxMessage->StdId & 0x7ffU;
    }
    else
        if(frame_format == FL_CAN_FORMAT_STANDARD_REMOTE) //标准远程帧
        {
            id = (TxMessage->StdId & 0x7ffU) | (0x01U << 11);
        }
        else
            if(frame_format == FL_CAN_FORMAT_EXTEND_DATA) //扩展数据帧
            {
                id = ((TxMessage->ExtId & 0x3ffffU) << 13) | (0x01U << 12) | (0x01U << 11) | ((TxMessage->ExtId & 0x1ffc0000U) >> 18);
            }
            else
                if(frame_format == FL_CAN_FORMAT_EXTEND_REMOTE) //扩展远程帧
                {
                    id = ((TxMessage->ExtId & 0x3ffffU) << 13) | (0x01U << 12) | (0x01U << 11) | (0x01U << 31) | ((TxMessage->ExtId & 0x1ffc0000U) >> 18);
                }


    len = TxMessage->DLC;
    data1 = (((uint32_t)TxMessage->Data[3] << 24) |
             ((uint32_t)TxMessage->Data[2] << 16) |
             ((uint32_t)TxMessage->Data[1] << 8) |
             ((uint32_t)TxMessage->Data[0]));
    data2 = (((uint32_t)TxMessage->Data[7] << 24) |
             ((uint32_t)TxMessage->Data[6] << 16) |
             ((uint32_t)TxMessage->Data[5] << 8) |
             ((uint32_t)TxMessage->Data[4]));

    FL_CAN_FIFO_Write(id, len, data1, data2);
    //    FL_CAN_HPBUF_Write(id,len,data1,data2);    //高优先级FIFO
}
