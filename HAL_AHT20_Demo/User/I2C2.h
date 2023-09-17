#ifndef __I2C2_H__
#define __I2C2_H__

/*头文件*/
#include "stm32f4xx.h"

/*用户自定义变量*/
#define I2C2_CLK_ENABLE __HAL_RCC_I2C2_CLK_ENABLE()
#define I2C2_Prot_CLK_ENABLE __HAL_RCC_GPIOF_CLK_ENABLE()
#define I2C2_Port GPIOF
#define I2C2_SDA GPIO_PIN_0
#define I2C2_SCL GPIO_PIN_1
extern I2C_HandleTypeDef I2C2_InitStruct;
/*用户函数声明*/
void I2C2_Init(void);
#endif



