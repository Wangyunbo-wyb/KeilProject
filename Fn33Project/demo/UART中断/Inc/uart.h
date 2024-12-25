#ifndef __UART_H__
#define __UART_H__
#include "main.h"


extern struct UARTOpStruct UARTxOp;
extern uint8_t tmp08;
extern uint8_t TestTxData[11];

void UART0_IRQHandler(void);
extern void UartxIRQ(UART_Type *UARTx);

#endif
