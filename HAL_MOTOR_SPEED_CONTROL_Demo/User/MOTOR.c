/*头文件*/
#include "MOTOR.h"

/*用户自定义变量*/
uint32_t Pulse = 0;
TIM_HandleTypeDef TIM2_InitStruct = {0};

/*电机转速控制函数*/
void PWM_Init(void)
{
	PWM_CLK_ENABLE;
    PWM_Port_CLK_ENABLE;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = PWM_Channel_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(PWM_Port, &GPIO_InitStruct);

	TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM2_InitStruct.Instance = TIM2;
    TIM2_InitStruct.Init.Prescaler = 167;
    TIM2_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIM2_InitStruct.Init.Period = 999;
    TIM2_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM2_InitStruct.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_PWM_Init(&TIM2_InitStruct);
   
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&TIM2_InitStruct, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&TIM2_InitStruct, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&TIM2_InitStruct, TIM_CHANNEL_1);

}


/*电机转速控制函数*/
void Motor_Control(void)
{    
    if(EC11_Count() < 1000u)
    {
        __HAL_TIM_SetCompare(&TIM2_InitStruct,TIM_CHANNEL_1,0);
    }
    else
    {		
		Pulse = (EC11_Count() - 265)/6;
		__HAL_TIM_SetCompare(&TIM2_InitStruct,TIM_CHANNEL_1,Pulse);
	}
}

