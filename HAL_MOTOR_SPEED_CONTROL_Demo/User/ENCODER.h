#ifndef __ENCODER_H__
#define __ENCODER_H__

/*头文件*/
#include "stm32f4xx.h"
#include "USART1.h"
#include "Delay.h"
/*用户自定义变量*/


#define Encoder_CLK_ENABLE __HAL_RCC_TIM3_CLK_ENABLE()
#define Encoder_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define Encoder_Port GPIOA
#define Encoder_A_Phase GPIO_PIN_6
#define Encoder_B_Phase GPIO_PIN_7


extern TIM_HandleTypeDef TIM3_InitStruct;
extern TIM_HandleTypeDef TIM4_InitStruct;

/*用户自定义函数*/
void Encoder_Init(void);
uint32_t Encoder_Count(void);
#endif

