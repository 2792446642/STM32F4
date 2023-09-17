/*头文件*/
#include "rcc.h"

/*用户自定义变量*/


/*系统时钟配置函数*/
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInittStruct = {0};		//定义晶振结构体变量
	RCC_ClkInitTypeDef RCC_CLKInitStruct = {0};		//定义时钟初始化结构体变量

	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);		//配置内部稳压器的输出电压
	

	RCC_OscInittStruct.HSEState = RCC_HSE_ON;		//开启外部高速晶振
	RCC_OscInittStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;		//使用外部晶振
	RCC_OscInittStruct.PLL.PLLState = RCC_PLL_ON;		//开启锁相环
	RCC_OscInittStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;		//选择锁相环来源为外部高速晶振
	RCC_OscInittStruct.PLL.PLLM = 4;		//PLLM的预分频系数为4
	RCC_OscInittStruct.PLL.PLLN = 168;		//PLLN的倍频系数为168
	RCC_OscInittStruct.PLL.PLLP = RCC_PLLP_DIV2;		//PLLP为2分频
	RCC_OscInittStruct.PLL.PLLQ = 4;		//PLLN的预分频系数为4
	while(HAL_RCC_OscConfig(&RCC_OscInittStruct) != HAL_OK);

	RCC_CLKInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;		//AHB总线时钟为1分频
	RCC_CLKInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;		//APB1总线时钟源来自AHB总线，最大时钟频率为42MHz，需要AHB总线4分频
	RCC_CLKInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;		//APB2总线时钟源来自AHB总线，最大时钟频率为84MHz，需要AHB总线2分频
	RCC_CLKInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;		//选择需要配置的总线时钟
	RCC_CLKInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;		//选择系统时钟来源为锁相环PLL时钟
	while(HAL_RCC_ClockConfig(&RCC_CLKInitStruct,FLASH_LATENCY_5));

	HAL_RCC_EnableCSS();
}





















