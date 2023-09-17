/* 硬件I2C的收发库函数会自动区分I2C器件的读写地址，
用户只需定义器件的写地址即可，
读地址库函数会自动在写地址的基础上+1 
(HAL_I2C_Master_Receive and HAL_I2C_Master_Transmit)*/
#ifndef __AHT20_H__
#define __AHT20_H__

/*头文件*/
#include "stm32f4xx.h"
#include "I2C2.h"
#include "USART1.h"
#include "Delay.h"
/*用户自定义变量*/
#define AHt20_Address 0x70
#define AHT20_TimeOut 1000

/*用户函数声明*/
void AHT20_Init(void);
void AHT20_Data_Read(float *humi,float *temp);
#endif

