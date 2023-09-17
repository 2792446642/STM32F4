/*头文件*/
#include "i2c2.h"

/*用户自定义变量*/
I2C_HandleTypeDef I2C2_InitStruct = {0};

/*I2C2硬件初始化函数*/
void I2C2_Init(void)
{
    I2C2_Prot_CLK_ENABLE;
    GPIO_InitTypeDef GPIO_InitStruct = {0};     //定义
    GPIO_InitStruct.Pin = I2C2_SDA;     //数据引脚
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;     //引脚复用开漏输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;     //输出无上、下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     //引脚速度非常快
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;      //引脚复用
    HAL_GPIO_Init(I2C2_Port, &GPIO_InitStruct);     //I2C硬件端口初始化

    GPIO_InitStruct.Pin = I2C2_SCL;     //时钟引脚
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;     //引脚复用开漏输出
    GPIO_InitStruct.Pull = GPIO_NOPULL;     //输出无上、下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;      //引脚速度非常快
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C2;      //引脚复用
    HAL_GPIO_Init(I2C2_Port, &GPIO_InitStruct);     //I2C硬件端口初始化

    I2C2_CLK_ENABLE;    //开启I2C2硬件时钟
    I2C2_InitStruct.Instance = I2C2;
    I2C2_InitStruct.Init.ClockSpeed = 100000;
    I2C2_InitStruct.Init.DutyCycle = I2C_DUTYCYCLE_2;
    I2C2_InitStruct.Init.OwnAddress1 = 0;
    I2C2_InitStruct.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    I2C2_InitStruct.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    I2C2_InitStruct.Init.OwnAddress2 = 0;
    I2C2_InitStruct.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    I2C2_InitStruct.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&I2C2_InitStruct);     //I2C2硬件配置初始化
}
