#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "key.h"
uint8_t KeyNUm;
float Angle;
int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"(^_^)(~3~)(^~^)");
	OLED_ShowString(2,1,"Angle:");
	Servo_Init();
	Key_Init();
	while(1){
		KeyNUm = Key_GetNum();
		if(KeyNUm == 1){
			Angle += 30;
			if(Angle > 180){
				Angle = 0;
			}	
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(2,7,Angle,3);
	}
}