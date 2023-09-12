#ifndef __I2C1_H__
#define __I2C1_H__

/*头文件*/
#include "stm32f4xx.h"

/*用户自定义变量*/
#define I2C1_CLK_ENABLE __HAL_RCC_I2C1_CLK_ENABLE()
#define I2C1_Prot GPIOB
#define I2C1_SDA GPIO_PIN_7
#define I2C1_CLK GPIO_PIN_6
extern I2C_HandleTypeDef I2C1_HandInit;

/*用户函数声明*/
void I2C1_Init(void);


#endif

