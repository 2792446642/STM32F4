/*头文件*/
#include "aht20.h"

/*用户自定义变量*/


/*AHT20设备检测函数*/
void AHT20_Init(void)
{   
    Delay_ms(40);       //延时40毫秒
    uint8_t Read_Data = 0;
	HAL_I2C_Master_Receive(&I2C2_InitStruct, AHt20_Address,&Read_Data,1,AHT20_TimeOut);     //读取AHT20的校准状态
    if((Read_Data & 0x18) == 0x18)      //读出值与校准状态字匹配
    {
        UART1_Transmit("AHT20已校准！ \r\n");
    }
    else    //读出值与校准状态字不匹配
    {
        UART1_Transmit("等待AHT20校准！ \r\n");
        uint8_t AHT20_Iint[3] = {0xBE,0x08,0x00};       //初始化命令数组
        HAL_I2C_Master_Transmit(&I2C2_InitStruct,AHt20_Address,AHT20_Iint,sizeof(AHT20_Iint),AHT20_TimeOut);    //向AHT20发送初始化命令
        if((Read_Data & 0x18) == 0x18)      //再次检测AHT20的校准状态
        {
            UART1_Transmit("AHT20校准完成！ \r\n");
        }
        else
        {
            UART1_Transmit("AHT20校准失败！ \r\n");
        }
    }
}

/*AHT20设备温湿度检测函数*/
void AHT20_Data_Read(float *humi,float *temp)
{
    uint8_t CMD[3] = {0xAC,0x33,0x00};
    uint8_t DataBuffer[6];
    uint32_t data = 0;
    HAL_I2C_Master_Transmit(&I2C2_InitStruct,AHt20_Address,CMD,sizeof(CMD),AHT20_TimeOut);      //发送读取温湿度数据指令
    Delay_ms(100);       //延时100毫秒
    HAL_I2C_Master_Receive(&I2C2_InitStruct,AHt20_Address,DataBuffer,sizeof(DataBuffer),AHT20_TimeOut);
    if((DataBuffer[0] & 0x80) == 0x80)
    {
         data = ((uint32_t)DataBuffer[1] << 12) + ((uint32_t)DataBuffer[2] << 4) + ((uint32_t)DataBuffer[3] >> 4);
        *humi = data * 100.0f/(1<<20);
        data = (((uint32_t)DataBuffer[3] & 0x0f) << 16) + ((uint32_t)DataBuffer[4] << 8) + (uint32_t)DataBuffer[5];
        *temp = data * 200.0f/(1<<20) - 50;
    }
    else
    {
        UART1_Transmit("AHT20已休眠！ \r\n");
    }
}



















