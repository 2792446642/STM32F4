/*头文件*/
#include "rcc.h"
#include "usart1.h"
#include "delay.h"
#include "stdint.h"
#include "EC11.h"

/*主函数*/
int main(void)
{
	SystemClock_Config();
	Delay_Init(168);
	EC11_Init();
	UART1_Init(115200);
	printf("welcome to mcu!\r\n");

	while(1)
	{
		// EC11_Driection();
	}
}
