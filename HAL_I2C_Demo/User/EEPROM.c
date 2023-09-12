/*头文件*/
#include "eeprom.h"

/*用户自定义变量*/


/*设备就绪检测函数*/
HAL_StatusTypeDef EEPROM_IsDeviceReady(void)
{
	uint32_t Trials = 10;		//尝试次数：10
	HAL_StatusTypeDef result = HAL_I2C_IsDeviceReady(&I2C1_HandInit, EEPROM_Write_Address, Trials, EEPROM_TimeOut);
	return result;
}

/*EEPROM单字节写入函数*/
HAL_StatusTypeDef EEPROM_Write_OneByte(uint16_t memAddress, uint8_t *Byte)
{
	HAL_StatusTypeDef result = HAL_I2C_Mem_Write(&I2C1_HandInit, EEPROM_Write_Address, memAddress, EEPROM_MEMADD_Size, Byte, 1, EEPROM_TimeOut);
	return result;
}

/*EEPROM单字节读取函数*/
HAL_StatusTypeDef EEPROM_Read_OneByte(uint16_t memAddress,uint8_t *Byte)
{
	HAL_StatusTypeDef result = HAL_I2C_Mem_Read(&I2C1_HandInit, EEPROM_Read_Address, memAddress, EEPROM_MEMADD_Size, Byte, 1, EEPROM_TimeOut);
	return result;
}

/*EEPROM连续字节读取函数*/
HAL_StatusTypeDef EEPROM_Continuously_Read(uint16_t memAddress,uint8_t *PData,uint16_t BufferLen)
{
	HAL_StatusTypeDef result = HAL_I2C_Mem_Read(&I2C1_HandInit, EEPROM_Read_Address, memAddress, EEPROM_MEMADD_Size, PData, BufferLen, EEPROM_TimeOut);
	return result;
}

/*EEPROM页写函数*/
HAL_StatusTypeDef EEPROM_Page_Write(uint16_t memAddress,uint8_t *Buffer,uint16_t BufferLen)
{
	if(BufferLen > EEPROM_Page_Size)
	{
		return HAL_ERROR;
	}
	HAL_StatusTypeDef result = HAL_I2C_Mem_Write(&I2C1_HandInit, EEPROM_Write_Address, memAddress, EEPROM_MEMADD_Size, Buffer, BufferLen, EEPROM_TimeOut);
	return result;
}

/*EEPROM写任意长度数据函数*/
HAL_StatusTypeDef EEPROM_AnyLongData_Write(uint16_t memAddress,uint8_t *Buffer,uint16_t BufferLen)
{
	uint16_t Page_Cont = BufferLen / EEPROM_Page_Size;		//得出数据集总页数
	uint16_t Rest = BufferLen % EEPROM_Page_Size;
	HAL_StatusTypeDef result;
	if(BufferLen < EEPROM_Page_Size)
	{
		result = HAL_I2C_Mem_Write(&I2C1_HandInit, EEPROM_Write_Address, memAddress, EEPROM_MEMADD_Size, Buffer, BufferLen, EEPROM_TimeOut);
		return result;
	}
	for(uint16_t i = 0;i < Page_Cont;i++)		//每执行一次for循环就写入一页数据
	{
		result = HAL_I2C_Mem_Write(&I2C1_HandInit, EEPROM_Write_Address, memAddress, EEPROM_MEMADD_Size, Buffer, EEPROM_Page_Size, EEPROM_TimeOut);
		Buffer += EEPROM_Page_Size;		//每次指针地址加8
		Delay_ms(5);		//延时5毫秒
		if(result != HAL_OK)
		{
			return HAL_ERROR;
		}
	}
	if(Rest > 0)
	{
		result =  HAL_I2C_Mem_Write(&I2C1_HandInit, EEPROM_Write_Address, memAddress, EEPROM_MEMADD_Size, Buffer, Rest, EEPROM_TimeOut);	
	}
	return HAL_ERROR;
}



















