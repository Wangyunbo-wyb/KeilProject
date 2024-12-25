#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//亮
	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	//灭
	//GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//Bit_RESET设置端口值，置低电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	//Bit_SET设置端口值，置高电平
	//GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
	while(1){
		GPIO_Write(GPIOA,~0x0001);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0002);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0004);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0008);
		Delay_ms(500);
		//GPIO_Write(GPIOA,~0x0010);
		//Delay_ms(500);
		//GPIO_Write(GPIOA,~0x0020);
		//Delay_ms(500);
	}
} 