/*头文件*/
#include "ec11.h"

/*用户自定义全局变量*/
uint32_t EC11_CNT = 1000;    //EC11计数变量
uint8_t EXTI9_5_IT_Flag = 0;
/*按键初始化函数*/
void EC11_Init(void)
{
	EC11_CLK_ENABLE;		//使能GPIOB端口时钟
	
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2); 	//中断分组为2
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);		//中断子优先级为0，抢占优先级为0
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);		//使能中断5~9

	GPIO_InitTypeDef GPIO_InitStruct = {0};		//定义GPIO结构体变量
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;		//GPIO模式为中断上拉触发
	GPIO_InitStruct.Pin = A_Phase;      //A相引脚(时钟线)
	GPIO_InitStruct.Pull = GPIO_PULLUP;		//引脚上拉
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;		//GPIO端口高速
	HAL_GPIO_Init(EC11_Port,&GPIO_InitStruct);		//使能KEY_PORT端口

	
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;		//GPIO配置为输入模式
	GPIO_InitStruct.Pin = B_Phase;      //B相引脚(数据线)
	GPIO_InitStruct.Pull = GPIO_NOPULL;		//引脚上拉
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;		//GPIO端口高速
	HAL_GPIO_Init(EC11_Port,&GPIO_InitStruct);		//使能KEY_PORT端口
}
/*EC11中断计数函数*/
uint32_t EC11_Count(void)
{
    if(EXTI9_5_IT_Flag == 1)
    {
        EXTI9_5_IT_Flag = 0;
        if(HAL_GPIO_ReadPin(EC11_Port,B_Phase) == GPIO_PIN_RESET)
        {
            if(HAL_GPIO_ReadPin(EC11_Port,B_Phase) == GPIO_PIN_RESET)
            {
                if(EC11_CNT > 0)
                {
                    EC11_CNT -= 100;
                    printf("main.t6.txt=\"设定转速:%d r/min\"\xff\xff\xff",EC11_CNT);
                }
            }                
        }
        if(HAL_GPIO_ReadPin(EC11_Port,B_Phase) == GPIO_PIN_SET)
        {
            
            if(HAL_GPIO_ReadPin(EC11_Port,B_Phase) == GPIO_PIN_SET)
            {
                if(EC11_CNT < 6000)
                {
                    EC11_CNT += 100;
                    printf("main.t6.txt=\"设定转速:%d r/min\"\xff\xff\xff",EC11_CNT);
                }              
            }
        }
    } 
    return EC11_CNT;
}

/*外部中断函数*/
void EXTI9_5_IRQHandler(void)
{
	if(__HAL_GPIO_EXTI_GET_IT(A_Phase) != RESET)        
    {
        __HAL_GPIO_EXTI_CLEAR_IT(A_Phase);
        EXTI9_5_IT_Flag = 1;
    }
}

