#ifndef __MPU9150_H_
#define __MPU9150_H_
# include "I2C.h"

//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define INT_PIN_CFG  	0x37	//
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define USER_CTRL		0x6A
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	Slave0Address	0xD0	//IIC写入时的地址字节数据，+1为读取
#define MPU9150_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU9150_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU9150_DEFAULT_ADDRESS     0xD0
/****************AK8975寄存器**************************/
#define MPU9150_RA_MAG_ADDRESS		0x0C
#define MPU9150_RA_MAG_ADDRESS1		0x0D
#define MPU9150_RA_MAG_ADDRESS2		0x0E
#define MPU9150_RA_MAG_ADDRESS3		0x0F
#define MPU9150_RA_MAG_DEFAULT_ADDRESS	 0x18

#define MPU9150_RA_MAG_XOUT_L		0x03
#define MPU9150_RA_MAG_XOUT_H		0x04
#define MPU9150_RA_MAG_YOUT_L		0x05
#define MPU9150_RA_MAG_YOUT_H		0x06
#define MPU9150_RA_MAG_ZOUT_L		0x07
#define MPU9150_RA_MAG_ZOUT_H		0x08
#define Device_ID 					0x00
#define Status1						0x02//0x01为Ready
#define Status2						0x09
#define ASAX						0x10   //Sensitivity Adjustment values
#define ASAY						0x11
#define ASAZ						0x12
#define CNTL						0x0A
#define ADJUST(Magn_data,Adujstdata)				     	Magn_data*((Adujstdata-128)*0.5/128.0+1)

typedef struct{
				s16 X;
				s16 Y;
				s16 Z;
	}S_INT16_XYZ;
extern S_INT16_XYZ		MPU6050_ACC_LAST,MPU6050_GYRO_LAST,MPU9150_MAG_LAST,MAGNETOMETERADJUSTDATA;		//最新一次读取值
extern s16 TEMP_LAST;
			

	//向I2C设备写入一个字节数据
u8 Single_WriteI2C(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
//从I2C设备读取一个字节数据
u8 Single_ReadI2C(u8 SlaveAddress,u8 REG_Address);
void InitMPU6050(void);
void UpdateData(void);
void GetMagnAdjustData(void);//获取磁力计校准数据.
	
	s16 GetData(u8 SlaveAddress,u8 REG_Address);

# endif
