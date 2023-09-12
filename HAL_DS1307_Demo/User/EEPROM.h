#ifndef __EEPROM_H__
#define __EEPROM_H__

/*头文件*/
#include "stm32f4xx.h"
#include "i2c1.h"
#include "delay.h"

/*用户自定义变量*/
#define EEPROM_Write_Address 0xA0
#define EEPROM_Read_Address 0xA1

// /* at24c02总共有256字节，每页8字节，共有32页 */
// #define EEPROM_Page_Size (uint8_t)8		//EEPROM页大小为8字节
// #define EEPROM_Mem_Size (uint8_t)256		//总容量字节数为256

/* at24c32总共有4096字节，每页32字节，共有128页 */
#define EEPROM_Page_Size (uint16_t)32		//EEPROM页大小为32字节
#define EEPROM_Mem_Size (uint16_t)4096		//总容量字节数为256

#define EEPROM_TimeOut 1000		//超时时间

// #define EEPROM_MEMADD_Size 1		//存储器地址大小为1字节(适用于at24c02~at24c16)
#define EEPROM_MEMADD_Size 2		//存储器地址大小为2字节(适用于at24c32及更大容量的EEPROM)

/*用户函数声明*/
HAL_StatusTypeDef EEPROM_IsDeviceReady(void);
HAL_StatusTypeDef EEPROM_Write_OneByte(uint16_t memAddress, uint8_t *Byte);
HAL_StatusTypeDef EEPROM_Read_OneByte(uint16_t memAddress,uint8_t *Byte);
HAL_StatusTypeDef EEPROM_Continuously_Read(uint16_t memAddress,uint8_t *PData,uint16_t BufferLen);
HAL_StatusTypeDef EEPROM_Page_Write(uint16_t memAddress,uint8_t *Buffer,uint16_t BufferLen);
HAL_StatusTypeDef EEPROM_AnyLongData_Write(uint16_t memAddress,uint8_t *Buffer,uint16_t BufferLen);

#endif

