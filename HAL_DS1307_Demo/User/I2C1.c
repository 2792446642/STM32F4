/*头文件*/
#include "i2c1.h"

/*用户自定义变量*/
I2C_HandleTypeDef I2C1_HandInit = {0};

/*I2C时钟、引脚初始化函数*/
void I2C1_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();		//开启GPIOB端口时钟
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;		//GPIO复用开漏模式
	GPIO_InitStruct.Pin = I2C1_SDA;		//配置I2C1数据线引脚
	GPIO_InitStruct.Pull = GPIO_NOPULL;		//配置I2C1时钟线引脚
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;		
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(I2C1_Prot, &GPIO_InitStruct);

	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pin = I2C1_CLK;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(I2C1_Prot, &GPIO_InitStruct);

	I2C1_CLK_ENABLE;		//开启I2C1外设时钟
	I2C1_HandInit.Instance = I2C1;		//寄存器基地址
	I2C1_HandInit.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;		//地址模式(7位)
	I2C1_HandInit.Init.ClockSpeed = 100000;		//时钟频率100kHZ
	I2C1_HandInit.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;		//双地址模式禁用
	I2C1_HandInit.Init.DutyCycle = I2C_DUTYCYCLE_2;		//时钟占空比
	I2C1_HandInit.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;		//广播模式禁用
	I2C1_HandInit.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;		//时钟延长禁止
	I2C1_HandInit.Init.OwnAddress1 = 0;		//作为从设备的主地址
	I2C1_HandInit.Init.OwnAddress2 = 0;		//作为从设备的副地址

	HAL_I2C_Init(&I2C1_HandInit);		//I2C1外设初始化
	
}












