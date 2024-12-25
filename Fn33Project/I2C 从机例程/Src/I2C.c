#include "I2C.h"

#define I2CREAD     1   //I2C主机读操作
#define I2CWRITE    0   //I2C主机写操作

uint8_t readdata[3];                       //接收的数据
uint8_t writedata[3] = {0x24, 0x55, 0x16}; //要发送的数据

void I2C_IRQHandler(void)
{
    uint32_t temp = 0;

    if((FL_ENABLE == FL_I2C_Slave_IsEnabledIT_AddressMatch(I2C))
            && (FL_SET == FL_I2C_Slave_IsActiveFlag_AddressMatch(I2C)))
    {

        temp = FL_I2C_Slave_ReadRXBuff(I2C);                            //读地址
        FL_I2C_Slave_ClearFlag_AddressMatch(I2C);
        FL_I2C_Slave_ClearFlag_RXComplete(I2C);

        if((temp & 0x01) == I2CWRITE)                     //主机写
        {
            while(!FL_I2C_Slave_IsActiveFlag_RXComplete(I2C));

            readdata[0] = FL_I2C_Slave_ReadRXBuff(I2C);
            FL_I2C_Slave_ClearFlag_RXComplete(I2C);

            while(!FL_I2C_Slave_IsActiveFlag_RXComplete(I2C));

            readdata[1] = FL_I2C_Slave_ReadRXBuff(I2C);
            FL_I2C_Slave_ClearFlag_RXComplete(I2C);

            while(!FL_I2C_Slave_IsActiveFlag_RXComplete(I2C));

            readdata[2] = FL_I2C_Slave_ReadRXBuff(I2C);
            FL_I2C_Slave_ClearFlag_RXComplete(I2C);

        }

        else
            if((temp & 0x01) == I2CREAD)              //主机读
            {

                FL_I2C_Slave_WriteTXBuff(I2C, writedata[0]);

                while(!FL_I2C_Slave_IsActiveFlag_TXComplete(I2C));

                FL_I2C_Slave_ClearFlag_TXComplete(I2C);

                FL_I2C_Slave_WriteTXBuff(I2C, writedata[1]);

                while(!FL_I2C_Slave_IsActiveFlag_TXComplete(I2C));

                FL_I2C_Slave_ClearFlag_TXComplete(I2C);

                FL_I2C_Slave_WriteTXBuff(I2C, writedata[2]);

                while(!FL_I2C_Slave_IsActiveFlag_TXComplete(I2C));

                FL_I2C_Slave_ClearFlag_TXComplete(I2C);
            }
    }

}






