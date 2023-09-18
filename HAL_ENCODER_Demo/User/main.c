/*头文件*/
#include "rcc.h"
#include "ENCODER.h"

/*用户自定义变量*/


/*主函数*/
int main(void)
{
	SystemClock_Config();		//初始化系统时钟配置
	Delay_Init(168);		//初始化延时函数配置
	UART1_Init(115200);		//初始化串口1配置
	Encoder_Init();		//初始化编码器配置
	while(1)
	{
		Encoder_Count();
	}
}






























