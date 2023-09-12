/*头文件*/
#include "rcc.h"
#include "key.h"
#include "eeprom.h"
#include "usart1.h"
#include "i2c1.h"
#include "delay.h"
/*主函数*/
int main(void)
{
	uint8_t AA = 10;		//AA变量存放待写入eeprom的数据为10
	uint8_t Data = 0;		//初始化读出数据存放空间变量
	
	uint8_t Lock_FLAG0 = 0;		//按键0自锁变量
	uint8_t Lock_FLAG1 = 0;		//按键1自锁变量

	HAL_Init();
	SystemClock_Config();		//系统时钟配置初始化
	Delay_Init(168);		//延时函数初始化(主频为168MHz)
	UART1_Init(115200);		//串口1初始化，波特率设置为115200
	printf("welcome to mcu!\r\n");		//上电打印指定字符
	KEY_Init();		//按键时钟开启及引脚初始化
	I2C1_Init();		//硬件I2C1配置初始化
	EEPROM_Write_OneByte(0x30,&AA);		//上电在eeprom地址为0x30的空间写入变量AA存放的数据(10)
	Delay_ms(10);		//延时10毫秒
	EEPROM_Read_OneByte(0x30,&Data);		//读出eeprom地址为0x30的空间中存放的数据
	Delay_ms(10);		//延时10毫秒
	printf("EEPROM读取地址:0x30\r\n");		//打印指定语句
	printf("EEPROM读出值:%d\r\n",Data);		//打印EEPROM读出值

	while(1)
	{
		if(KEY_0_FLAG == 1)
		{
			if(HAL_GPIO_ReadPin(KEY_PORT, KEY_0) == RESET)
			{
				if(HAL_GPIO_ReadPin(KEY_PORT, KEY_0) == RESET)
				{
					if(Lock_FLAG0 == 0)
					{
						Lock_FLAG0 = 1;
						AA -= 1;
						EEPROM_Write_OneByte(0x30,&AA);
						Delay_ms(10);
						EEPROM_Read_OneByte(0x30,&Data);
						Delay_ms(10);
						printf("写入的值为:%d\r\n",Data);
					}
				}
			}
		}
		if(KEY_1_FLAG == 1)
		{
			if(HAL_GPIO_ReadPin(KEY_PORT, KEY_1) == RESET)
			{
				if(HAL_GPIO_ReadPin(KEY_PORT, KEY_1) == RESET)
				{
					if(Lock_FLAG1 == 0)
					{
						Lock_FLAG1 = 1;
						AA += 1;
						EEPROM_Write_OneByte(0x30,&AA);
						Delay_ms(10);
						EEPROM_Read_OneByte(0x30,&Data);
						Delay_ms(10);
						printf("写入的值为:%d\r\n",Data);
					}
				}
			}
		}
		if(HAL_GPIO_ReadPin(KEY_PORT, KEY_0) == SET)
		{
			KEY_0_FLAG = 0;
			Lock_FLAG0 = 0;
		}
		if(HAL_GPIO_ReadPin(KEY_PORT, KEY_1) == SET)
		{
			KEY_1_FLAG = 0;
			Lock_FLAG1 = 0;
		}
	}
}
