#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "(^_^)(~3~)(^~^)");
	Serial_Init();
	uint8_t MyArray[] = {0x41, 0x42, 0x43, 0x44};
	Serial_SendByte(0x41);
	//Serial_SendArray(MyArray, 4);
	//Serial_SendString("Hello World!\r\n")
	//Serial_SendNumber(12345,5);
	//printf("Num=%d\r\n",666);
	while (1)
	{
	}
}