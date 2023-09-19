/*头文件*/
#include "encoder.h"

/*用户自定义变量*/

TIM_HandleTypeDef TIM3_InitStruct = {0};
TIM_HandleTypeDef TIM4_InitStruct = {0};
uint8_t TIM4_IT_Flag = 0;
uint16_t Count = 0;
uint8_t Dir = 0;
float Speed = 0;

/*编码器初始化配置函数*/
void Encoder_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    TIM_Encoder_InitTypeDef TIM3_Encoder_InitStruct = {0};
    TIM_MasterConfigTypeDef  TIM3_MasterConfigInitStruct = {0};
    
    TIM_ClockConfigTypeDef TIM4_sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef TIM4_sMasterConfig = {0};

    Encoder_CLK_ENABLE;     //开启定时器编码器模块时钟
    Encoder_Port_CLK_ENABLE;    //开启定时器编码器端口时钟
    GPIO_InitStruct.Pin = Encoder_A_Phase;      //编码器A相引脚
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;     //引脚设置为复用推挽输出模式
    GPIO_InitStruct.Pull = GPIO_NOPULL;     //无上、下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;      //引脚输出速度设置为非常快(50~100MHz)
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;      //定时器3的复用模式
    HAL_GPIO_Init(Encoder_Port, &GPIO_InitStruct);      //编码器端口初始化

    GPIO_InitStruct.Pin = Encoder_B_Phase;      //编码器B相引脚
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;     //引脚设置为复用推挽输出模式
    GPIO_InitStruct.Pull = GPIO_NOPULL;     //无上、下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;      //引脚输出速度设置为非常快(50~100MHz)
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;      //定时器3的复用模式
    HAL_GPIO_Init(Encoder_Port, &GPIO_InitStruct);      //编码器端口初始化

    TIM3_InitStruct.Instance = TIM3;        //定时器3
    TIM3_InitStruct.Init.Prescaler = 0;     //预分频系数为0
    TIM3_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;      //向上计数模式
    TIM3_InitStruct.Init.Period = 65535;    //预装载值为65535
    TIM3_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    //定时器时钟不分频
    TIM3_InitStruct.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;       //失能自动重装功能
    TIM3_Encoder_InitStruct.EncoderMode = TIM_ENCODERMODE_TI12;     //编码器设置为双端口模式
    TIM3_Encoder_InitStruct.IC1Polarity = TIM_ICPOLARITY_RISING;    //上升沿捕获
    TIM3_Encoder_InitStruct.IC1Selection = TIM_ICSELECTION_DIRECTTI;
    TIM3_Encoder_InitStruct.IC1Prescaler = TIM_ICPSC_DIV1;
    TIM3_Encoder_InitStruct.IC1Filter = 6;      //过滤器设置为6
    TIM3_Encoder_InitStruct.IC2Polarity = TIM_ICPOLARITY_RISING;    //上升沿捕获
    TIM3_Encoder_InitStruct.IC2Selection = TIM_ICSELECTION_DIRECTTI;
    TIM3_Encoder_InitStruct.IC2Prescaler = TIM_ICPSC_DIV1;
    TIM3_Encoder_InitStruct.IC2Filter = 6;      //过滤器设置为6
    HAL_TIM_Encoder_Init(&TIM3_InitStruct,&TIM3_Encoder_InitStruct);    //定时器编码模式初始化

    TIM3_MasterConfigInitStruct.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM3_MasterConfigInitStruct.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM3_InitStruct, &TIM3_MasterConfigInitStruct);

    __HAL_RCC_TIM4_CLK_ENABLE();        //开启定时器4硬件时钟
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);     //中断分组为2
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);      //定时器4的抢占优先级为0，子优先级为0
    HAL_NVIC_EnableIRQ(TIM4_IRQn);      //使能定时器4定时中断
    TIM4_InitStruct.Instance = TIM4;    //定时器4
    TIM4_InitStruct.Init.Prescaler = 8399;      //预分频系数为8400，即频率0.0001s/次
    TIM4_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;      //向上计数模式
    TIM4_InitStruct.Init.Period = 4999;     //每隔0.5秒进入中断
    TIM4_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;    //预分频系数设置为1
    TIM4_InitStruct.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;    //失能自动重装载预装载功能
    HAL_TIM_Base_Init(&TIM4_InitStruct);        //定时器4配置初始化

    TIM4_sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;      //定时时钟来源为单片机内部
    HAL_TIM_ConfigClockSource(&TIM4_InitStruct, &TIM4_sClockSourceConfig);       //定时器4时钟源配置初始化

    TIM4_sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    TIM4_sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM4_InitStruct, &TIM4_sMasterConfig);

    HAL_TIM_Base_Start_IT(&TIM4_InitStruct);       //启动定时器4
    HAL_TIM_Encoder_Start(&TIM3_InitStruct,TIM_CHANNEL_ALL);       //启动定时器3编码器计数功能
}


/*定时器3编码器模块计数函数*/
uint32_t Encoder_Count(void)
{    
    if(TIM4_IT_Flag == 1)       //500毫秒执行一次
    {
        TIM4_IT_Flag = 0;       //清零定时中断标志变量
        Dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(&TIM3_InitStruct);     //获取转向信息
        Count = __HAL_TIM_GetCounter(&TIM3_InitStruct);     //获取编码器计数值      
        if(Dir == 1)    //电机反转
        {
            if(Count != 0)
            {
                Count = 65535 - Count;
            }           
        }
        Speed = (float)(Count/100.0f/2.0f)*60.0f;       //计算电机实时转速
        printf("main.t2.txt=\"当前转速: %.2f r/min\"\xff\xff\xff",Speed);       //打印电机转速到串口屏
        __HAL_TIM_SET_COUNTER(&TIM3_InitStruct,0);      //计数值清0
    }
    return (Count/100/2)*60;
}


/*定时器4中断函数*/
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_InitStruct);       //清除中断标志位
    TIM4_IT_Flag = 1;       //置1定时中断标志变量
}

