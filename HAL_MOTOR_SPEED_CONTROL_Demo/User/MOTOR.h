#ifndef __MOTOR_H__
#define __MOTOR_H__

/*头文件*/
#include "stm32f4xx.h"
#include "EC11.h"
#include "ENCODER.h"
/*用户自定义变量*/
#define PWM_CLK_ENABLE __HAL_RCC_TIM2_CLK_ENABLE()
#define PWM_Port_CLK_ENABLE __HAL_RCC_GPIOA_CLK_ENABLE()
#define PWM_Port GPIOA
#define PWM_Channel_1 GPIO_PIN_0

extern TIM_HandleTypeDef TIM2_InitStruct;

/*用户函数声明*/
void PWM_Init(void);
void Motor_Control(void);
#endif
