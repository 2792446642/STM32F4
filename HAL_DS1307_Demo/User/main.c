/*头文件*/
#include "rcc.h"
#include "key.h"
#include "ds1307.h"
#include "usart1.h"
#include "usart2.h"
#include "i2c1.h"
#include "stdint.h"
#include "eeprom.h"

uint8_t cnt = 0;

/*主函数*/
int main(void)
{
	uint8_t AA = 0;
	uint8_t Data = 0;

	uint8_t eeprom_Wdata = 123;
	uint8_t eeprom_Rdata = 0;


	uint8_t Hour_Change = 0;
	uint8_t Minute_Change = 0;
	uint8_t Second_Change = 0;
	uint8_t Year_Change = 0;
	uint8_t Month_Change = 0;
	uint8_t Day_Change = 0;

	uint8_t Year = 0x23;
	uint8_t Hour = 0x19;
	uint8_t Month = 0x09;
	uint8_t Day = 0x11;
	uint8_t Second = 0x30;
	uint8_t Minute = 0x14;

	uint8_t Lock_FLAG0 = 0;
	uint8_t Lock_FLAG1 = 0;

	HAL_Init();
	SystemClock_Config();
	Delay_Init(168);
	UART1_Init(9600);
	UART2_Init(115200);
	printf("welcome to mcu!\r\n");
	KEY_Init();
	I2C1_Init();

	DS1307_Write_OneByte(0x00,&AA);
	Delay_ms(10);
	DS1307_Write_OneByte(0x04,&Day);
	Delay_ms(10);
	DS1307_Write_OneByte(0x05,&Month);
	Delay_ms(10);
	DS1307_Write_OneByte(0x06,&Year);
	Delay_ms(10);
	DS1307_Write_OneByte(0x00,&Second);
	Delay_ms(10);
	DS1307_Write_OneByte(0x01,&Minute);
	Delay_ms(10);
	DS1307_Write_OneByte(0x02,&Hour);
	Delay_ms(10);
	DS1307_Read_OneByte(0x00,&Second);
	DS1307_Read_OneByte(0x01,&Minute);
	DS1307_Read_OneByte(0x02,&Hour);
	DS1307_Read_OneByte(0x04,&Day);
	DS1307_Read_OneByte(0x05,&Month);
	DS1307_Read_OneByte(0x06,&Year);
	Delay_ms(10);
	printf("main.n0.val=%x\xff\xff\xff",Hour);
	printf("main.n1.val=%x\xff\xff\xff",Minute);
	printf("main.n2.val=%x\xff\xff\xff",Second);
	printf("main.n3.val=%x\xff\xff\xff",Year);
	printf("main.n4.val=%x\xff\xff\xff",Month);
	printf("main.n5.val=%x\xff\xff\xff",Day);
	EEPROM_Write_OneByte(0x20,&eeprom_Wdata);
	Delay_ms(10);
	EEPROM_Read_OneByte(0x20,&eeprom_Rdata);
	Delay_ms(10);
	printf("main.t2.txt=\"%d\"\xff\xff\xff",eeprom_Rdata);

	while(1)
	{
		DS1307_Read_OneByte(0x00,&Second);
		DS1307_Read_OneByte(0x01,&Minute);
		DS1307_Read_OneByte(0x02,&Hour);
		DS1307_Read_OneByte(0x04,&Day);
		DS1307_Read_OneByte(0x05,&Month);
		DS1307_Read_OneByte(0x06,&Year);
		if(Year_Change != Year)
		{
			printf("main.n3.val=%x\xff\xff\xff",Year);
		}
		if(Month_Change != Month)
		{
			printf("main.n4.val=%x\xff\xff\xff",Month);
		}
		if(Day_Change != Day)
		{
			printf("main.n5.val=%x\xff\xff\xff",Day);
		}
		if(Hour_Change != Hour)
		{
			printf("main.n0.val=%x\xff\xff\xff",Hour);
		}
		if(Minute_Change != Minute)
		{
			printf("main.n1.val=%x\xff\xff\xff",Minute);
		}
		if(Second_Change != Second)
		{
			printf("main.n2.val=%x\xff\xff\xff",Second);
			EEPROM_Write_OneByte(0x234,&Second);		//
			Delay_ms(10);		//
			EEPROM_Read_OneByte(0x234,&eeprom_Rdata);	//
			printf("main.t2.txt=\"0x%x\"\xff\xff\xff",eeprom_Rdata);		//
		}
		Hour_Change = Hour;
		Minute_Change = Minute;
		Second_Change = Second;
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
						DS1307_Write_OneByte(0x00,&AA);
						Delay_ms(10);
						DS1307_Read_OneByte(0x00,&Data);
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
						DS1307_Write_OneByte(0x00,&AA);
						Delay_ms(10);
						DS1307_Read_OneByte(0x00,&Data);
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
