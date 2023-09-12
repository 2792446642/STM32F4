#ifndef __DS1307_H__
#define __DS1307_H__

/*头文件*/
#include "stm32f4xx.h"
#include "stdint.h"
#include "i2c1.h"
#include "delay.h"
/*用户自定义变量*/

#define DS1307_Write_Address 0xD0
#define DS1307_Read_Address 0xD1

#define DS1307_TimeOut 1000		//超时时间
#define DS1307_MEMADD_Size 1		//存储器地址大小为1字节

/*用户函数声明*/
HAL_StatusTypeDef DS1307_IsDeviceReady(void);
HAL_StatusTypeDef DS1307_Write_OneByte(uint16_t memAddress, uint8_t *Byte);
HAL_StatusTypeDef DS1307_Read_OneByte(uint16_t memAddress,uint8_t *Byte);

#endif

