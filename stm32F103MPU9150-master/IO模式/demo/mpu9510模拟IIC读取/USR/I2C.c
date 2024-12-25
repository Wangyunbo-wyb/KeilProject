#include "pbdata.h"

void I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = I2C_SCL | I2C_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C, &GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

void I2C_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = I2C_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
}

void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = I2C_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C, &GPIO_InitStructure);
}

// ??????????
void I2C_Start(void)
{
	I2C_SDA_OUT();

	I2C_SDA_H;
	I2C_SCL_H;
	delay_us(5);
	I2C_SDA_L;
	delay_us(5);
	I2C_SCL_L;
}

// ?????????
void I2C_Stop(void)
{
	I2C_SDA_OUT();

	// I2C_SCL_L;//**********************
	I2C_SDA_L;
	delay_us(1);
	I2C_SCL_H;

	delay_us(5);
	I2C_SDA_H;
	delay_us(5);
}

// ??????????????ACK
void I2C_Ack(void)
{
	I2C_SCL_L;
	I2C_SDA_OUT();
	I2C_SDA_L;
	delay_us(2);
	I2C_SCL_H;
	delay_us(5);
	I2C_SCL_L;
}

// ????????????????NACK
void I2C_NAck(void)
{
	I2C_SCL_L;
	I2C_SDA_OUT();
	I2C_SDA_H;
	delay_us(2);
	I2C_SCL_H;
	delay_us(5);
	I2C_SCL_L;
}
// ????????????
// ???????1 ??????????
//		  0 ?????????
u8 I2C_Wait_Ack(void)
{
	u8 tempTime = 0;

	I2C_SDA_IN();

	I2C_SDA_H;
	I2C_SCL_L; //*********************
	delay_us(1);
	I2C_SCL_H;
	delay_us(1);

	while (GPIO_ReadInputDataBit(GPIO_I2C, I2C_SDA))
	{
		tempTime++;
		if (tempTime > 255)
		{
			I2C_Stop();
			return 0;
		}
	}

	I2C_SCL_L;
	return 1;
}
// I2C ??????????
void I2C_Send_Byte(u8 txd)
{
	u8 i = 0;

	I2C_SDA_OUT();
	I2C_SCL_L; // ????????????????

	for (i = 0; i < 8; i++)
	{
		if ((txd & 0x80) > 0) // 0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;
		delay_us(2);
		txd <<= 1;
		I2C_SCL_H;
		delay_us(5); // ????????
		I2C_SCL_L;
		delay_us(5);
	}
	// I2C_Wait_Ack();//********************************************************************
}

// I2C ?????????

u8 I2C_Read_Byte(u8 ack)
{
	u8 i = 0, receive = 0;
	delay_us(2);
	I2C_SDA_IN();
	for (i = 0; i < 8; i++)
	{
		I2C_SCL_L;
		delay_us(1);
		I2C_SCL_H;
		receive <<= 1;
		if (GPIO_ReadInputDataBit(GPIO_I2C, I2C_SDA))
			receive++;
		delay_us(1);
	}

	if (ack == 0)
		I2C_NAck();
	else
		I2C_Ack();

	return receive;
}
