	I2C_MPU6050_Init(); 	//IIC�ӿڳ�ʼ��
  InitMPU6050();  
  
  	GetData(ACCEL_XOUT_H)//���ٶ�X��ԭʼ����
	GetData(ACCEL_YOUT_H) //���ٶ�Y��ԭʼ����
	GetData(ACCEL_ZOUT_H)   //���ٶ�Z��ԭʼ����
		
	GetData(GYRO_XOUT_H)  //������X��ԭʼ����
	GetData(GYRO_YOUT_H)    //������Y��ԭʼ����
	GetData(GYRO_ZOUT_H)    //������Z��ԭʼ����
	GetData(TEMP_OUT_H)/340.0+35.0    //�¶�