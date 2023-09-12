#ifndef __USART2_H__
#define __USART2_H__

/*头文件*/
#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>
/*用户自定义变量*/

#define USART2_Port GPIOA
#define USART2_TX GPIO_PIN_2
#define USART2_RX GPIO_PIN_3

#define USART2_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART2_CLK_ENABLE __HAL_RCC_USART2_CLK_ENABLE()

#define FRAME_Start 0x99		//定义起始帧为0x99
#define FRAME_End 0x55	//定义结束帧为0x55
#define FRAME_Error_Start 0x1a		//错误帧
#define FRAME_Error_End 0xff		//错误结束帧
#define UART_Rx_Data_LEN 200		//接收存储区空间大小


extern uint8_t Rx_Data[];
/*用户自定义函数*/
void UART2_Init(uint32_t BaudRate);
void UART2_Transmit(uint8_t *TX_Data);
void UART2_Receive_Transmit(void);

#endif

