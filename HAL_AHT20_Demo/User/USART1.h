#ifndef __USART1_H__
#define __USART1_H__

/*头文件*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

/*用户自定义变量*/
#define USART1_Port GPIOA
#define USART1_TX GPIO_PIN_9
#define USART1_RX GPIO_PIN_10


#define USART1_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART1_CLK_ENABLE __HAL_RCC_USART1_CLK_ENABLE()

#pragma diag_suppress 77,550,1294,1295
#pragma diag_suppress 870

/*用户自定义函数*/
void UART1_Init(uint32_t BaudRate);
int fputc(int ch, FILE *f);
void UART1_Transmit(uint8_t *TX_Data);

#endif

