#ifndef __EEPROM_H__
#define __EEPROM_H__

/*头文件*/
#include "stm32f4xx.h"
#include "i2c1.h"
#include "delay.h"
/*用户自定义变量*/

#define EEPROM_Write_Address 0xA0
#define EEPROM_Read_Address 0xA1

#define EEPROM_Page_Size 8		//EEPROM页大小为8字节
#define EEPROM_Mem_Size 256		//总容量字节数为256

#define EEPROM_TimeOut 1000		//超时时间
#define EEPROM_MEMADD_Size 1		//存储器地址大小为1字节
/*用户函数声明*/
HAL_StatusTypeDef EEPROM_IsDeviceReady(void);
HAL_StatusTypeDef EEPROM_Write_OneByte(uint16_t memAddress, uint8_t *Byte);
HAL_StatusTypeDef EEPROM_Read_OneByte(uint16_t memAddress,uint8_t *Byte);
HAL_StatusTypeDef EEPROM_Continuously_Read(uint16_t memAddress,uint8_t *PData,uint16_t BufferLen);
HAL_StatusTypeDef EEPROM_Page_Write(uint16_t memAddress,uint8_t *Buffer,uint16_t BufferLen);
HAL_StatusTypeDef EEPROM_AnyLongData_Write(uint16_t memAddress,uint8_t *Buffer,uint16_t BufferLen);

#endif

