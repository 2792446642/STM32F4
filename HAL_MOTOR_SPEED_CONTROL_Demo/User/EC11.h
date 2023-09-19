#ifndef __EC11_H__
#define __EC11_H__

/*头文件*/
#include "stm32f4xx.h"
#include "Delay.h"
#include "USART1.h"

/*用户自定义变量*/
#define EC11_Port GPIOB     //旋转编码器引脚端口
#define A_Phase GPIO_PIN_8      //A相引脚
#define B_Phase GPIO_PIN_9      //B相引脚
#define EC11_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE()    //旋转编码器时钟

/*用户自定义函数*/
void EC11_Init(void);
uint32_t EC11_Count(void);
#endif

