#ifndef __ENCODER_H__
#define __ENCODER_H__

/*头文件*/
#include "stm32f4xx.h"
#include "USART1.h"
#include "Delay.h"
/*用户自定义变量*/
#define PWM_CLK_ENABLE __HAL_RCC_TIM2_CLK_ENABLE()
#define PWM_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define PWM_Port GPIOA
#define PWM_Channel_1 GPIO_PIN_0

#define Encoder_CLK_ENABLE __HAL_RCC_TIM3_CLK_ENABLE()
#define Encoder_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define Encoder_Port GPIOA
#define Encoder_A_Phase GPIO_PIN_6
#define Encoder_B_Phase GPIO_PIN_7

extern TIM_Encoder_InitTypeDef TIM_Encoder_InitStruct;
extern TIM_MasterConfigTypeDef  TIM_MasterConfigInitStruct;

/*用户自定义函数*/
void Encoder_Init(void);
void Encoder_Count(void);
#endif

