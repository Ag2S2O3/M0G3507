#ifndef __UART_H
#define __UART_H
#include "ti_msp_dl_config.h"

void UART_Init(void);
void UART_0_INST_IRQHandler(void);
uint8_t UART_Recive(void);
uint8_t UART_GetFlag(void);
float UART_ReturnM1(void);
float UART_ReturnM2(void);
void Data_Decoder(uint8_t data);
#endif