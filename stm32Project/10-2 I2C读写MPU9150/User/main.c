#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "mpu9150.h"
int main(void)
{
	OLED_Init();
	MYI2C_Init();
	InitMPU6050();
	UpdateData6050();
	OLED_ShowString(1,1,"The numbers are");
	while (1)
	{
		UpdateData6050();
		OLED_ShowNum(2, 1, MPU6050_ACC_LAST.X, 8);
		OLED_ShowNum(3, 1, MPU6050_ACC_LAST.Y, 8);
		OLED_ShowNum(4, 1, MPU6050_ACC_LAST.Z, 8);
		//--*****OLED_ShowNum(2, 1, MPU6050_GYRO_LAST.X, 8);
		delay_ms(500);
	}
}