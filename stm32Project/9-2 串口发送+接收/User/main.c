#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;
int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "(^_^)(~3~)(^~^)");
	//OLED_ShowBinNum(3,1,21,2);
	Serial_Init();
	while (1)
	{
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
		{
			RxData = USART_ReceiveData(USART1);
			OLED_ShowHexNum(2, 1, RxData, 2);
		}
	}
}