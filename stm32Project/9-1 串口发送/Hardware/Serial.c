#include "stm32f10x.h" // Device header
#include <stdio.h>
#include <stdarg.h>
void Serial_Init(void)
{
    // 开启时钟，把需要用的USART和GPIO的时钟打开
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // GPIO初始化，TX配置为复用输出，RX配置为输入
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    // 配置USART
    USART_InitTypeDef USART_InitStructure;
    // 波特率数值
    USART_InitStructure.USART_BaudRate = 9600;
    // 硬件流控制
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    // 串口模式
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    // 校验位
    USART_InitStructure.USART_Parity = USART_Parity_No;
    // 停止位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ;
}
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}

void Serial_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++)
    {
        Serial_SendByte(String[i]);
    }
}
uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    while (y--)
    {
        result *= x;
    }
    return result;
}
void Serial_SendNumber(uint32_t Number, uint8_t Len)
{
    uint8_t i;
    for (i = 0; i < Len; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10, Len - i - 1) % 10 + '0');
    }
}

int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

void Serial_Printf(char *format,...){
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);
	

