/*头文件*/
#include "usart2.h"

/*用户自定义变量*/
UART_HandleTypeDef UART2_HandleInit = {0};
uint16_t UART_Tx_Data_LEN = 0;		//要发送数据的长度

uint8_t FRAME_Start_FLAG = 0;
uint8_t FRAME_Error_FLAG = 0;
uint8_t Rx_State_FLAG = 0;		//接收数据状态标志

uint16_t Rx_Buffer_Count = 0;		//接收数据存储区位置计数变量
uint8_t Rx_Data[UART_Rx_Data_LEN] = {0};		//接收中断数据存储区(100个X1字节)
uint8_t Rx_Buffer[1];		//接收中断数据缓冲区(1字节)

/*串口2初始化函数*/
void UART2_Init(uint32_t BaudRate)
{
	UART2_HandleInit.Instance = USART2;
	UART2_HandleInit.Init.BaudRate = BaudRate;		//设置串口2波特率
	UART2_HandleInit.Init.Parity = UART_PARITY_NONE;		//无奇偶校验
	UART2_HandleInit.Init.StopBits = UART_STOPBITS_1;		//一位停止位
	UART2_HandleInit.Init.WordLength = UART_WORDLENGTH_8B;		//串口2字长为8位
	UART2_HandleInit.Init.Mode = UART_MODE_TX_RX;		//串口2设置为收发模式
	UART2_HandleInit.Init.HwFlowCtl = UART_HWCONTROL_NONE;		//无硬件流控制
	UART2_HandleInit.Init.OverSampling = UART_OVERSAMPLING_16;		//16次过采样，容错性更好

	USART2_Port_CLK_ENABLE;
	USART2_CLK_ENABLE;

	GPIO_InitTypeDef GPIO_InitStruct = {0};		
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;		
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;		//复用推挽模式
	GPIO_InitStruct.Pull = GPIO_NOPULL;		//无上下拉
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;		//最高速度
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;		//复用通道7选择串口2
	HAL_GPIO_Init(USART2_Port,&GPIO_InitStruct);		//初始化串口2接收引脚
	
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);		//设置中断嵌套分组为2
	HAL_NVIC_SetPriority(USART2_IRQn,0,0);		//设置中断抢占优先级为0，子优先级为0
	HAL_NVIC_EnableIRQ(USART2_IRQn);		//开启USART1中断
	
	HAL_UART_Init(&UART2_HandleInit);		//初始化串口2
	
	HAL_UART_Receive_IT(&UART2_HandleInit,(uint8_t *)Rx_Buffer,1);		//初始化首次使能串口2接收非空中断
}

/*串口2printf重定向函数*/
int fputc(int ch, FILE *f)
{ 
	HAL_UART_Transmit(&UART2_HandleInit,(uint8_t *)&ch,1,1000);   //将要发送的字符写入到DR寄存器	
	while(__HAL_UART_GET_FLAG(&UART2_HandleInit, UART_FLAG_TC) == RESET);
	return ch;
}

/*串口2阻塞式发送数据函数*/
void UART2_Transmit(uint8_t *TX_Data)
{
	uint32_t i = 0;
	__HAL_UART_CLEAR_FLAG(&UART2_HandleInit, UART_FLAG_TC);		//清除串口发送完成标志位
	while(TX_Data[i] != '\0')
	{
		HAL_UART_Transmit(&UART2_HandleInit,(uint8_t *)&TX_Data[i],1,1000);		//发送用户指定字符串
		while(__HAL_USART_GET_FLAG(&UART2_HandleInit,UART_FLAG_TC) == RESET);		//等待串口2上一次数据发送完成
		__HAL_UART_CLEAR_FLAG(&UART2_HandleInit, UART_FLAG_TC);		//再次清除
		i++;
	}
}

/*串口2中断式接收并发送数据函数*/
void UART2_Receive_Transmit(void)
{
	if(Rx_State_FLAG == 1)		//判断是否已经接收完成
	{
		Rx_State_FLAG = 0;		//置0接收数据状态标志，等待下一次数据接收完成
		FRAME_Start_FLAG = 0;
		UART_Tx_Data_LEN = Rx_Buffer_Count;		//获取接收到数据的长度，作为要发送数据的长度
		HAL_UART_Transmit(&UART2_HandleInit,(uint8_t *)Rx_Data,UART_Tx_Data_LEN,1000);		//发送接收到的数据至串口助手
		while(__HAL_UART_GET_FLAG(&UART2_HandleInit, UART_FLAG_TC) != SET);		//等待数据发送完成
		printf("\r\n数据发送完成！\r\n");
		printf("数据占用总空间为:%d\r\n",UART_Tx_Data_LEN);
		Rx_Buffer_Count = 0;		//清空接收存储空间计数
	}
}

/*串口2中断服务函数*/
void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&UART2_HandleInit);		//HAL库串口2中断服务函数(清零数据缓冲寄存器，关闭相应中断。此函数会调用中断回调函数)	
	HAL_UART_Receive_IT(&UART2_HandleInit,(uint8_t *)Rx_Buffer,1);		//再次使能串口2接收非空中断
}

/*串口2中断服务回调函数*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)                     /* 如果是串口2 */
	{
		if(Rx_Buffer[0] == FRAME_Start || FRAME_Start_FLAG == 1)		//判断第一帧数据是否为0x99
		{
			FRAME_Start_FLAG = 1;		//第一帧数据为起始帧，帧开始标志置1
			if(Rx_Buffer[0] == FRAME_End)		//判断第二帧是否为0x55
			{
				//是结束帧，数据接收完成
				FRAME_Start_FLAG = 0;		
				Rx_Buffer_Count = 0;		//清空接收存储空间计数
//				UART_Tx_Data_LEN = Rx_Buffer_Count;		//获取接收到数据的长度，作为要发送数据的长度
//				HAL_UART_Transmit(&UART2_HandleInit,(uint8_t *)Rx_Data,UART_Tx_Data_LEN,1000);		//发送接收到的数据至串口助手
//				while(__HAL_UART_GET_FLAG(&UART2_HandleInit, UART_FLAG_TC) != SET);		//等待数据发送完成
//				printf("\r\n数据发送完成！\r\n");
//				printf("数据占用总空间为:%d\r\n",UART_Tx_Data_LEN);
			}
			else if(Rx_Buffer[0] != FRAME_End && FRAME_Start_FLAG == 1)		//不是结束帧并且起始帧为0x99
			{	
				Rx_Data[Rx_Buffer_Count] = Rx_Buffer[0];		//将当次接收中断的数据存放到接收中断数据存储区相应位置
				Rx_Buffer_Count++;		//Rx_Buffer_Count自动加1
				if(Rx_Buffer_Count > (UART_Rx_Data_LEN - 1))
				{
					Rx_State_FLAG = 0;             /* 接收数据错误,重新开始接收 */
					printf("接收到的数据容量大于指定存储空间的大小！\r\n");		      
				}
			}
		}
//		else		//若第一帧不是起始帧，打印出错提示
//		{
//			printf("起始帧错误，请输入正确起始帧!(0x40)\xff\xff\xff");
//		}
	}	
}






