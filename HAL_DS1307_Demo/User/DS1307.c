/*头文件*/
#include "ds1307.h"

/*用户自定义变量*/


/*设备就绪检测函数*/
HAL_StatusTypeDef DS1307_IsDeviceReady(void)
{
	uint32_t Trials=10;		//尝试次数：10
	HAL_StatusTypeDef result = HAL_I2C_IsDeviceReady(&I2C1_HandInit, DS1307_Write_Address, Trials, DS1307_TimeOut);
	return result;
}

/*DS1307单字节写入函数*/
HAL_StatusTypeDef DS1307_Write_OneByte(uint16_t memAddress, uint8_t *Byte)
{
	HAL_StatusTypeDef result = HAL_I2C_Mem_Write(&I2C1_HandInit, DS1307_Write_Address, memAddress, DS1307_MEMADD_Size, Byte, 1, DS1307_TimeOut);
	return result;
}

/*DS1307单字节读取函数*/
HAL_StatusTypeDef DS1307_Read_OneByte(uint16_t memAddress,uint8_t *Byte)
{
	HAL_StatusTypeDef result = HAL_I2C_Mem_Read(&I2C1_HandInit, DS1307_Read_Address, memAddress, DS1307_MEMADD_Size, Byte, 1, DS1307_TimeOut);
	return result;
}


















