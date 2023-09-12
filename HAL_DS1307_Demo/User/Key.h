#ifndef __KEY_H__
#define __KEY_H__

/*头文件*/
#include "stm32f4xx.h"
#include "ds1307.h"
/*用户宏定义及变量*/
#define KEY_PORT GPIOB

#define KEY_0 GPIO_PIN_9
#define KEY_1 GPIO_PIN_8


extern uint8_t KEY_0_FLAG;
extern uint8_t KEY_1_FLAG;



/*用户函数声明*/
void KEY_Init(void);


#endif


