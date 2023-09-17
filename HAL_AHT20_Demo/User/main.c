/*头文件*/
#include "rcc.h"
#include "AHT20.h"

/*用户自定义变量*/
// uint8_t a = 0xac;
float Temperature = 0;
float Humidity = 0;
/*主函数*/
int main(void)
{
	SystemClock_Config();		//初始化系统时钟配置
	Delay_Init(168);		//延时函数配置初始化
	UART1_Init(115200);
	I2C2_Init();		//硬件I2C2初始化
	AHT20_Init();

	while(1)
	{
		AHT20_Data_Read(&Humidity,&Temperature);
		printf("湿度：%.2f",Humidity);
		printf("温度：%.2f\r\n",Temperature);
		Delay_ms(1000);
	}
}






























