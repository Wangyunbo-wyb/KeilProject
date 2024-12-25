#ifndef __CAN_H__
#define __CAN_H__

#include "main.h"



typedef struct
{
    uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

    uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

    uint8_t DLC;     /*!< Specifies the length of the frame that will be
                        transmitted. This parameter can be a value between
                        0 to 8 */

    uint8_t Data[8]; /*!< Contains the data to be transmitted. It ranges from 0
                        to 0xFF. */
} CanTxMsg;
extern CanTxMsg TxMessage;


typedef struct
{
    uint32_t StdId;  /*!< Specifies the standard identifier.
                        This parameter can be a value between 0 to 0x7FF. */

    uint32_t ExtId;  /*!< Specifies the extended identifier.
                        This parameter can be a value between 0 to 0x1FFFFFFF. */

    uint8_t DLC;     /*!< Specifies the length of the frame that will be received.
                        This parameter can be a value between 0 to 8 */

    uint8_t Data[8]; /*!< Contains the data to be received. It ranges from 0 to
                        0xFF. */
} CanRxMsg;

extern void FL_CAN_FIFO_Write(uint32_t id, uint32_t len, uint32_t data1, uint32_t data2);
extern void FL_CAN_HPBUF_Write(uint32_t id, uint32_t len, uint32_t data1, uint32_t data2);
void FL_CAN_FIFO_Read(void);
void CAN_SetMsg(CanTxMsg *TxMessage);
void FL_CAN_Frame_Send(uint32_t frame_format, CanTxMsg *TxMessage);
#endif

