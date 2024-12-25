# include "mpu9150.h"

S_INT16_XYZ		MPU6050_ACC_LAST,MPU6050_GYRO_LAST,MPU9150_MAG_LAST,MAGNETOMETERADJUSTDATA;		//最新一次读取值
int16_t TEMP_LAST;

//**************************************
//向I2C设备写入一个字节数据
//**************************************
u8 Single_WriteI2C(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
    I2C_Start();                  //起始信号
    I2C_Send_Byte(SlaveAddress);   //发送设备地址+写信号
		if(!I2C_Wait_Ack())
			return 0;
    I2C_Send_Byte(REG_Address);    //内部寄存器地址，
		if(!I2C_Wait_Ack())
			return 0;
    I2C_Send_Byte(REG_data);       //内部寄存器数据，
		if(!I2C_Wait_Ack())
			return 0;
    I2C_Stop();                   //发送停止信号
		delay_us(5);
		return 1;
}
//**************************************
//从I2C设备读取一个字节数据
//**************************************
u8 Single_ReadI2C(u8 SlaveAddress,u8 REG_Address)
{
	u8 REG_data;
	I2C_Start();                   //起始信号
	I2C_Send_Byte(SlaveAddress);    //发送设备地址+写信号
	if(!I2C_Wait_Ack())
			return 0;
	I2C_Send_Byte(REG_Address);     //发送存储单元地址，从0开始	
	if(!I2C_Wait_Ack())
			return 0;
	
	I2C_Start();                   //起始信号
	I2C_Send_Byte(SlaveAddress+1);  //发送设备地址+读信号
	if(!I2C_Wait_Ack())
			return 0;
	
	REG_data=I2C_Read_Byte(0);      //读出寄存器数据 无应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}
void InitMPU6050()
{
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,INT_PIN_CFG, 0x02);
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,USER_CTRL, 0x07);
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,SMPLRT_DIV, 0x07);
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,CONFIG, 0x06);
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,GYRO_CONFIG, 0x18);//设置陀螺仪精度，测量范围
	Single_WriteI2C(MPU9150_DEFAULT_ADDRESS,ACCEL_CONFIG, 0x01);//设置加速度量程
}

//**************************************
//合成数据
//**************************************
s16 GetData(u8 SlaveAddress,u8 REG_Address)//加速度计和角速度计的数据合成
{
	u8 H,L;
	H=Single_ReadI2C(SlaveAddress,REG_Address);
	L=Single_ReadI2C(SlaveAddress,REG_Address+1);
	return (H<<8)+L;   //合成数据
}
s16 GetData2(u8 SlaveAddress,u8 REG_Address)//磁力计数据合成
{
	u8 H=0,L=0;
	L=Single_ReadI2C(SlaveAddress,REG_Address);
	H=Single_ReadI2C(SlaveAddress,REG_Address+1);
	return (H<<8)+L;   //合成数据
}
void GetMagnAdjustData()//获取磁力计校准数据
{
	Single_WriteI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,CNTL, 0x0f);	   //Single measurement mode
	MAGNETOMETERADJUSTDATA.X=Single_ReadI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,ASAX);
	MAGNETOMETERADJUSTDATA.Y=Single_ReadI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,ASAY);
	MAGNETOMETERADJUSTDATA.Z=Single_ReadI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,ASAZ);
	Single_WriteI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,CNTL, 0x00);	  //Power-down mode
}
void UpdateData6050()
{
	//三轴加速度计数据
		MPU6050_ACC_LAST.X=GetData(MPU9150_DEFAULT_ADDRESS,ACCEL_XOUT_H);
		MPU6050_ACC_LAST.Y=GetData(MPU9150_DEFAULT_ADDRESS,ACCEL_YOUT_H);
		MPU6050_ACC_LAST.Z=GetData(MPU9150_DEFAULT_ADDRESS,ACCEL_ZOUT_H);
		
	//三轴角速度计数据
		MPU6050_GYRO_LAST.X=GetData(MPU9150_DEFAULT_ADDRESS,GYRO_XOUT_H);
		MPU6050_GYRO_LAST.Y=GetData(MPU9150_DEFAULT_ADDRESS,GYRO_YOUT_H);
		MPU6050_GYRO_LAST.Z=GetData(MPU9150_DEFAULT_ADDRESS,GYRO_ZOUT_H);
	
	//温度数据
		TEMP_LAST=GetData(MPU9150_DEFAULT_ADDRESS,TEMP_OUT_H);
}
void UpdateData9150()
{
	 s8 Status2_= 0;
	//三轴加速度计数据
		MPU6050_ACC_LAST.X=GetData(MPU9150_DEFAULT_ADDRESS,ACCEL_XOUT_H);
		MPU6050_ACC_LAST.Y=GetData(MPU9150_DEFAULT_ADDRESS,ACCEL_YOUT_H);
		MPU6050_ACC_LAST.Z=GetData(MPU9150_DEFAULT_ADDRESS,ACCEL_ZOUT_H);
		
	//三轴角速度计数据
		MPU6050_GYRO_LAST.X=GetData(MPU9150_DEFAULT_ADDRESS,GYRO_XOUT_H);
		MPU6050_GYRO_LAST.Y=GetData(MPU9150_DEFAULT_ADDRESS,GYRO_YOUT_H);
		MPU6050_GYRO_LAST.Z=GetData(MPU9150_DEFAULT_ADDRESS,GYRO_ZOUT_H);
	
	//温度数据
		TEMP_LAST=GetData(MPU9150_DEFAULT_ADDRESS,TEMP_OUT_H);
	//磁力计数据

		Single_WriteI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,CNTL, 0x01);	   //Single measurement mode
		while(!Single_ReadI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,Status1));//数据未准备好时等待
		MPU9150_MAG_LAST.X=GetData2(MPU9150_RA_MAG_DEFAULT_ADDRESS,MPU9150_RA_MAG_XOUT_L);
		MPU9150_MAG_LAST.Y=GetData2(MPU9150_RA_MAG_DEFAULT_ADDRESS,MPU9150_RA_MAG_YOUT_L);
		MPU9150_MAG_LAST.Z=GetData2(MPU9150_RA_MAG_DEFAULT_ADDRESS,MPU9150_RA_MAG_ZOUT_L);
		Status2_=Single_ReadI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,Status2);
		if((Status2_&0x04)==0x04||(Status2_&0x08)==0x08)	  //Is Data read error occurred or Magnetic sensor overflow occurred？
		{
			MPU9150_MAG_LAST.X=0x6fff;//数据为0x6fff时表示数据有错
			MPU9150_MAG_LAST.Y=0x6fff;
			MPU9150_MAG_LAST.Z=0x6fff;	
		}	
		Single_WriteI2C(MPU9150_RA_MAG_DEFAULT_ADDRESS,CNTL, 0x00);	  //Power-down mode	 
		MPU9150_MAG_LAST.X=ADJUST(MPU9150_MAG_LAST.X,MAGNETOMETERADJUSTDATA.X);
		MPU9150_MAG_LAST.Y=ADJUST(MPU9150_MAG_LAST.Y,MAGNETOMETERADJUSTDATA.Y);
		MPU9150_MAG_LAST.Z=ADJUST(MPU9150_MAG_LAST.Z,MAGNETOMETERADJUSTDATA.Z);
}
