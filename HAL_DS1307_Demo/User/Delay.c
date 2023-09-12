/*头文件*/
#include "delay.h"

/*用户自定义变量*/
u32 systick_Freq = 0;


/*用户自定义函数*/
//延时函数初始化
void Delay_Init(u32 SYSCLK_Freq)
{	
	SysTick->CTRL = 0;		//系统滴答时钟控制寄存器全部置零
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);		//系统滴答定时器8分频
	systick_Freq = SYSCLK_Freq/21;		//获取系统滴答时钟频率(MHz)
}

//微秒级延时函数
void Delay_us(u32 us)
{
	u32 temp = 0;
	SysTick->LOAD = us*systick_Freq;		//自动重装载寄存器赋值
	SysTick->VAL = 0;		//清空计数器
	SysTick->CTRL |= 1<<0;	//开启滴答定时器
	do
	{
		temp = SysTick->CTRL;		//将滴答定时器的控制寄存器值赋给temp
	}while((temp & 0x01)&&!(temp&(1<<16)));		//等待计数器值减为零
	SysTick->CTRL |= !(1<<0);		//关闭滴答定时器
	SysTick->VAL = 0;		//清零计数器
}
//毫秒级延时函数
void Delay_ms(u32 ms)
{
	u32 temp = 0;
	SysTick->LOAD = ms*1000*systick_Freq;		//自动重装载寄存器赋值
	SysTick->VAL = 0;		//清空计数器
	SysTick->CTRL |= 1<<0;	//开启滴答定时器
	do
	{
		temp = SysTick->CTRL;		//将滴答定时器的控制寄存器值赋给temp
	}while((temp & 0x01)&&!(temp&(1<<16)));		//等待计数器值减为零
	SysTick->CTRL |= !(1<<0);		//关闭滴答定时器
	SysTick->VAL = 0;		//清零计数器
}






































