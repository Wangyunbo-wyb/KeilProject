#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "I2C_MPU6050.h"
int main(void)
{
	OLED_Init();
	OLED_ShowString(1, 1, "The numbers are");
	I2C_MPU6050_Init(); // IIC接口初始化
	InitMPU6050();
	int16_t signx = GetData(ACCEL_XOUT_H);
	while (1)
	{
		OLED_ShowNum(2, 1, signx, 16);
		// OLED_ShowNum(3, 1, MPU6050_ACC_LAST.Y, 8);
		// OLED_ShowNum(4, 1, MPU6050_ACC_LAST.Z, 8);
		//--*****OLED_ShowNum(2, 1, MPU6050_GYRO_LAST.X, 8);
	}
}