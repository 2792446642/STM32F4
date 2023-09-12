/*头文件*/
#include "key.h"

/*用户宏定义及变量*/
uint8_t KEY_0_FLAG = 0;		//中断9触发标志变量
uint8_t KEY_1_FLAG = 0;		//中断8触发标志变量


/*按键初始化函数*/
void KEY_Init(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();		//使能GPIOB端口时钟
	
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2); 	//中断分组为2
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);		//中断子优先级为0，抢占优先级为0
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);		//使能中断5~9

	GPIO_InitTypeDef GPIO_InitStruct = {0};		//定义GPIO结构体变量
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;		//GPIO模式为中断下拉触发
	GPIO_InitStruct.Pin = KEY_0;	
	GPIO_InitStruct.Pull = GPIO_PULLUP;		//引脚上拉
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		//GPIO端口高速
	HAL_GPIO_Init(KEY_PORT,&GPIO_InitStruct);		//使能KEY_PORT端口

	
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;		//GPIO模式为中断下拉触发
	GPIO_InitStruct.Pin = KEY_1;
	GPIO_InitStruct.Pull = GPIO_PULLUP;		//引脚上拉
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;		//GPIO端口高速
	HAL_GPIO_Init(KEY_PORT,&GPIO_InitStruct);		//使能KEY_PORT端口
}

/*外部中断函数*/
void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(KEY_0);
	HAL_GPIO_EXTI_IRQHandler(KEY_1);
}


/*外部中断回调函数*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(GPIO_Pin)
	{
		case KEY_0:
			KEY_0_FLAG = 1;
			break;
		case KEY_1:
			KEY_1_FLAG = 1;
			break;
	}
}































