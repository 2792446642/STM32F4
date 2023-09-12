#ifndef __DELAY_H__
#define __DELAY_H__

/*头文件*/
#include "stm32f4xx.h"
/*用户自定义变量*/
#define u32 unsigned int
/*用户函数声明*/
void Delay_Init(u32 SYSCLK_Freq);
void Delay_us(u32 us);
void Delay_ms(u32 ms);
#endif













