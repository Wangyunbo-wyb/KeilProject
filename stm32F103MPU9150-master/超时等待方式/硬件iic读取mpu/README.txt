	I2C_MPU6050_Init(); 	//IIC接口初始化
  InitMPU6050();  
  
  	GetData(ACCEL_XOUT_H)//加速度X轴原始数据
	GetData(ACCEL_YOUT_H) //加速度Y轴原始数据
	GetData(ACCEL_ZOUT_H)   //加速度Z轴原始数据
		
	GetData(GYRO_XOUT_H)  //陀螺仪X轴原始数据
	GetData(GYRO_YOUT_H)    //陀螺仪Y轴原始数据
	GetData(GYRO_ZOUT_H)    //陀螺仪Z轴原始数据
	GetData(TEMP_OUT_H)/340.0+35.0    //温度