#ifndef _DEBUG_UART_H
#define _DEBUG_UART_H

#include "system.h"
// #include "pub.h"
#include "stdio.h"
// #include "comm_rec.h"

//´®¿ÚÑ¡Ôñ 1~3

#define DEBUG_UARTx         USART1
#define DEBUG_UARTx_BAUD    115200
#define DEBUG_UARTx_IRQ     USART1_IRQHandler


void Debug_Uart_Init(void);
void Usart_SendBuf(u8 *buf,vu16 len);
uint16_t Usart_RecvData(void);

#endif
