#include "aes.h"
#include <string.h>

/**
  * @brief  Word内的字节交换
  * @param  pWord 输入参数：带交换的指针地址；pWord 输出参数：交换后的指针地址
  * @param  length  交换的Word长度
  * @retval None
  */
static void ByteExChange(uint32_t *pWord, uint32_t length)
{

    uint32_t i = 0;
    uint32_t value = 0;
    uint32_t *pRam;
    if(pWord == NULL) { return; }
    pRam = pWord;

    for(i = 0; i < length; i++)
    {
        value = (uint32_t)((*pRam & 0xFFUL) << 24) + (uint32_t)(((*pRam & 0xFF00UL) >> 8) << 16) + (uint32_t)(((*pRam & 0xFF0000UL) >> 16) << 8) + (uint32_t)(*pRam >> 24);
        *pRam++ = value;
    }
}

/**
  * @brief  设置MultH运算128bit输入H参数(h0存放密钥最低32bit)
  * @param  H参数 16字节长度的密钥
  * @param  长度  16
  * @retval None
  */
void AES_H_WriteEx(uint8_t *hxIn)
{
    uint32_t i;
    uint32_t temp32;
    if(hxIn == NULL) { return; }

    for(i = 0; i < 16; i = i + 4)
    {
        temp32 = (((uint32_t)(hxIn[0 + i]) << 24) | (((uint32_t)hxIn[1 + i]) << 16) | (((uint32_t)hxIn[2 + i]) << 8) | (uint32_t)hxIn[3 + i]);
        FL_AES_WriteHParams(AES, (uint32_t)((16 - i) / 4 - 1), temp32);
    }

}

/**
  * @brief  读取MultH运算128bit输入H参数(h0存放密钥最低32bit)
  * @param  H参数 16字节长度的密钥
  * @param  长度  16
  * @retval None
  */
void AES_H_ReadEx(uint8_t *hxOut)
{
    uint32_t i;
    uint32_t temp32;

    if(hxOut == NULL) { return; }
    for(i = 0; i < 16; i = i + 4)
    {
        temp32 = FL_AES_ReadHParams(AES, (uint32_t)((16 - i) / 4 - 1));
        hxOut[0 + i] = (uint8_t)(temp32 >> 24);
        hxOut[1 + i] = (uint8_t)(temp32 >> 16);
        hxOut[2 + i] = (uint8_t)(temp32 >> 8);
        hxOut[3 + i] = (uint8_t)temp32;
    }
}


/**
  * @brief  设置加解密密钥(key0存放密钥最低32bit)
  * @param  密钥  16/24/32字节长度的密钥
  * @param  长度  16/24/32
  * @retval None
  */
void AES_KEY_WriteEx(uint8_t *keyIn, uint32_t len)
{
    uint32_t i;
    uint32_t temp32;

    if((len != 16) && (len != 24) && (len != 32)) { return; }
    if(keyIn == NULL) { return; }

    for(i = 0; i < len; i = i + 4)
    {
        temp32 = ((uint32_t)(keyIn[0 + i]) << 24) | ((uint32_t)(keyIn[1 + i]) << 16) | ((uint32_t)(keyIn[2 + i]) << 8) | keyIn[3 + i];
        FL_AES_WriteKeys(AES, (uint32_t)((len - i) / 4 - 1), temp32);
    }

}

/**
  * @brief  读取加解密密钥，第一个字存放密钥最低32bit
  * @param  密钥  16/24/32字节长度的密钥
  * @param  长度  16/24/32
  * @retval None
  */
void AES_KEY_ReadEx(uint8_t *keyOut, uint32_t len)
{
    uint32_t i;
    uint32_t temp32;

    if(keyOut == NULL) { return; }
    if((len != 16) && (len != 24) && (len != 32)) { return; }

    for(i = 0; i < len; i = i + 4)
    {
        temp32 = FL_AES_ReadKeys(AES, (uint32_t)((len - i) / 4 - 1));
        keyOut[0 + i] = (uint8_t)(temp32 >> 24);
        keyOut[1 + i] = (uint8_t)(temp32 >> 16);
        keyOut[2 + i] = (uint8_t)(temp32 >> 8);
        keyOut[3 + i] = (uint8_t)temp32;
    }
}

/**
  * @brief  设置初始向量
  * @param  初始向量
  * @retval None
  */
void AES_IVR_WriteEx(uint8_t *ivrIn)
{
    uint32_t i;
    uint32_t temp32;

    if(ivrIn == NULL) { return; }
    for(i = 0; i < 4 * 4; i = i + 4)
    {
        temp32 = (((uint32_t)ivrIn[0 + i]) << 24) | (((uint32_t)ivrIn[1 + i]) << 16) | (((uint32_t)ivrIn[2 + i]) << 8) | (uint32_t)ivrIn[3 + i];
        FL_AES_WriteIVR(AES, (uint32_t)((16 - i) / 4 - 1), temp32);
    }
}

/**
  * @brief  读取初始向量
  * @param  初始向量
  * @retval None
  */

void AES_IVR_ReadEx(uint8_t *ivrOut)
{
    uint32_t i;
    uint32_t temp32;

    if(ivrOut == NULL) { return; }
    for(i = 0; i < 4 * 4; i = i + 4)
    {
        temp32 = FL_AES_ReadIVR(AES, (uint32_t)((4 * 4 - i) / 4 - 1));
        ivrOut[0 + i] = (uint8_t)(temp32 >> 24);
        ivrOut[1 + i] = (uint8_t)(temp32 >> 16);
        ivrOut[2 + i] = (uint8_t)(temp32 >> 8);
        ivrOut[3 + i] = (uint8_t)temp32;
    }
}

/**
  * @brief  设置加解密数据，16字节（128bit）分组数据输入
  * @param  初始向量
  * @retval None
  */

void AES_DIN_GroupWrite_128BIT(uint8_t *dataIn)
{
    uint32_t i;
    uint32_t temp32;

    if(dataIn == NULL) { return; }
    for(i = 0; i < 16; i = i + 4)
    {
        temp32 = (((uint32_t)dataIn[0 + i]) << 24) | (((uint32_t)dataIn[1 + i]) << 16) | (((uint32_t)dataIn[2 + i]) << 8) | (uint32_t)dataIn[3 + i];
        FL_AES_WriteInputData(AES, temp32);
    }
}

/**
  * @brief  加解密数据输出，16字节（128bit）分组数据输出
  * @param  初始向量
  * @retval None
  */

void AES_DOUT_GroupRead_128BIT(uint8_t *dataOut)
{
    uint32_t i;
    uint32_t temp32;

    if(dataOut == NULL) { return; }
    for(i = 0; i < 16; i = i + 4)
    {
        temp32 = FL_AES_ReadOutputData(AES);
        dataOut[0 + i] = (uint8_t)(temp32 >> 24);
        dataOut[1 + i] = (uint8_t)(temp32 >> 16);
        dataOut[2 + i] = (uint8_t)(temp32 >> 8);
        dataOut[3 + i] = (uint8_t)temp32;
    }
}

/**
  * @brief  先设置16字节（128bit）加密数据，然后再读取16字节（128bit）解密数据
  * @param  加密数据
  * @param  解密数据
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 成功
  *         -FL_FAIL 失败
  */
FL_ErrorStatus AES_GroupWriteAndRead_128BIT(uint8_t *dataIn, uint8_t *dataOut)
{
    uint16_t i;

    if((dataIn == NULL) || (dataOut == NULL)) { return FL_FAIL; }
    /* 输入加解密数据 */
    AES_DIN_GroupWrite_128BIT(dataIn);

    /* 等待CCF标志置起,完成计算大约需要100个时钟周期 */
    for(i = 0; i < 500; i++)
    {
        if(0X01 == FL_AES_IsActiveFlag_Complete(AES)) { break; }
    }

    /* 清CCF标志 */
    /* 读取前必须清除 */
    FL_AES_ClearFlag_Complete(AES);

    /* 读取结果 */
    AES_DOUT_GroupRead_128BIT(dataOut);

    if(i == 500) { return FL_FAIL; }

    else { return FL_PASS; }
}


/**
  * @brief  先设置16字节（128bit）加密数据，然后再读取16字节（128bit）解密数据
  * @param  加密数据
  * @param  解密数据
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 成功
  *         -FL_FAIL 失败
  */

FL_ErrorStatus AES_GroupWriteAndRead_128BIT_IVR(uint8_t *dataIn, uint8_t *dataOut)
{
    uint16_t i;

    if((dataIn == NULL) || (dataOut == NULL)) { return FL_FAIL; }
    /* 输入加解密数据 */
    AES_DIN_GroupWrite_128BIT(dataIn);

    /* 等待CCF标志置起,完成计算大约需要100个时钟周期 */
    for(i = 0; i < 500; i++)
    {
        if(0X01 == FL_AES_IsActiveFlag_Complete(AES)) { break; }
    }

    /* 清CCF标志，读取前必须清除 */
    FL_AES_ClearFlag_Complete(AES);

    /* 读取结果 */
    AES_IVR_ReadEx(dataOut);

    if(i == 500) { return FL_FAIL; }

    else { return FL_PASS; }
}

/**
  * @brief  AES初始化函数
    * @param  KeyLenth This parameter can be one of the following values:
  *           @arg @ref FL_AES_KEY_LENGTH_128B
  *           @arg @ref FL_AES_KEY_LENGTH_192B
  *           @arg @ref FL_AES_KEY_LENGTH_256B
    * @param    CipherMode This parameter can be one of the following values:
  *           @arg @ref FL_AES_CIPHER_ECB
  *           @arg @ref FL_AES_CIPHER_CBC
  *           @arg @ref FL_AES_CIPHER_CTR
  *           @arg @ref FL_AES_CIPHER_MULTH
    * @param    OperationMode This parameter can be one of the following values:
  *           @arg @ref FL_AES_OPERATION_MODE_ENCRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION
  *           @arg @ref FL_AES_OPERATION_MODE_DECRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION
    * @param    DataType This parameter can be one of the following values:
  *           @arg @ref FL_AES_DATA_TYPE_32B
  *           @arg @ref FL_AES_DATA_TYPE_16B
  *           @arg @ref FL_AES_DATA_TYPE_8B
  *           @arg @ref FL_AES_DATA_TYPE_1B
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */
FL_ErrorStatus AES_Init(uint32_t KeyLength, uint32_t CipherMode, uint32_t OperationMode, uint32_t DataType)
{
    FL_AES_InitTypeDef AES_InitStructer;
    /********************加密过程********************/
    /* 重置AES模块 */
    (void)FL_AES_DeInit();
    /* 设置 AES_InitStruct 为默认配置 */
    FL_AES_StructInit(&AES_InitStructer);
    AES_InitStructer.keyLength      = KeyLength;
    AES_InitStructer.cipherMode    = CipherMode;
    AES_InitStructer.operationMode = OperationMode;
    AES_InitStructer.dataType      = DataType;
    /* AES_InitStructer初始化对应外设入口地址的寄存器值 */
    return FL_AES_Init(AES, &AES_InitStructer);
}

/**
  * @brief  AES加解密处理流程
  * @note   DataOut指针空间由调用者申请，空间大小必须是16字节的整数倍（因为即使是不足16字节的数据进行加密，AES处理不足16字节会进行补零操作，然后再进行加解密）
    * @param    KeyIn 密钥指针
    * @param    KeyLen 密钥长度
    * @param    IVRIn 向量指针
    * @param    DataIn 加密输入数据指针
    * @param    DataInLen 加密数据输入长度
    * @param    DataOut 解密输出数据指针
    * @param    DataOutLen 解密输出长度
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */

FL_ErrorStatus AES_EncryptionAndDecryption(uint8_t *keyIn, uint32_t keyLen, uint8_t *ivrIn, uint8_t *dataIn, uint32_t dataInLen, uint8_t *dataOut, uint32_t *dataOutLen)
{
    uint32_t i;
    FL_ErrorStatus result = FL_FAIL;
    uint8_t tempBuf[16];
    if((keyIn == NULL) || (dataIn == NULL) || (dataOut == NULL) || (dataOutLen == NULL)) { return FL_FAIL; }
    /* 设置密钥 */
    if(FL_AES_GetCipherMode(AES) != FL_AES_CIPHER_MULTH)
    {
        AES_KEY_WriteEx(keyIn, keyLen);
    }

    else
    {
        AES_H_WriteEx(keyIn);
    }

    /* CTR和CBC模式下写AES_IVRx寄存器 */
    if(FL_AES_GetCipherMode(AES) != FL_AES_CIPHER_ECB)
    {
        if(ivrIn != NULL)
        {
            AES_IVR_WriteEx(ivrIn);
        }
    }

    /* 启动AES */
    FL_AES_Enable(AES);

    for(i = 0; i < dataInLen / 16; i++)
    {
        /* 获取AES模式 */
        if(FL_AES_GetCipherMode(AES) == FL_AES_CIPHER_MULTH)
        {
            /* 读取AES计算结果 */
            result = AES_GroupWriteAndRead_128BIT_IVR(dataIn + 16 * i, dataOut + 16 * i);

            if(result == FL_FAIL) { return FL_FAIL; }
        }

        else
        {
            /* 读取AES计算结果 */
            result = AES_GroupWriteAndRead_128BIT(dataIn + 16 * i, dataOut + 16 * i);

            if(result == FL_FAIL) { return FL_FAIL; }
        }
    }

    if((dataInLen % 16) != 0)
    {
        /* 不足16字节进行补零操作 */
        memset((void *)tempBuf, 0, (size_t)(sizeof(tempBuf)));
        memcpy((void *)tempBuf, (const void *)(dataIn + i * 16), (size_t)(dataInLen - i * 16));

        /* 获取AES模式 */
        if(FL_AES_GetCipherMode(AES) == FL_AES_CIPHER_MULTH)
        {
            /* 读取AES计算结果 */
            result = AES_GroupWriteAndRead_128BIT_IVR(tempBuf, dataOut + i * 16);

            if(result == FL_FAIL) { return FL_FAIL; }
        }

        else
        {
            /* 读取AES计算结果 */
            result = AES_GroupWriteAndRead_128BIT(tempBuf, dataOut + i * 16);

            if(result == FL_FAIL) { return FL_FAIL; }
        }
    }

    /* 返回加解密之后的数据长度 */
    if(FL_AES_GetCipherMode(AES) == FL_AES_CIPHER_CTR)
    {
        *dataOutLen = dataInLen;
    }

    else
    {
        *dataOutLen = ((dataInLen + 15) / 16) * 16;
    }

    /* 关闭AES模块 */
    FL_AES_Disable(AES);
    return FL_PASS;
}





/**
  * @brief  AES的ECB模式测试程序
  * @param  None
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */
FL_ErrorStatus AES_ECB_Encrypt(void)
{
    uint8_t dataInBuf[16] = {0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x30U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    uint8_t keyBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x31U};
    uint8_t ivrBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x32U};
    uint8_t dataOut[16] = {0x00};
    uint32_t dataOutLen;
    const uint8_t scrResultBuf[16] = {0x17U, 0x6CU, 0xF5U, 0x23U, 0x86U, 0xCDU, 0x8AU, 0x11U, 0x9FU, 0x78U, 0x15U, 0x94U, 0x72U, 0x38U, 0xE3U, 0xF5U};
    int32_t result;
    FL_ErrorStatus status;
    /********************加密过程********************/
    status = AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 10, dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, 16);
    if(result != 0) { return FL_FAIL; }

    return FL_PASS;

}

/**
  * @brief  AES的ECB模式解密测试程序
  * @param  void
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */
FL_ErrorStatus AES_ECB_Decrypt(void)
{
    uint8_t dataInBuf[16] = {0x17U, 0x6CU, 0xF5U, 0x23U, 0x86U, 0xCDU, 0x8AU, 0x11U, 0x9FU, 0x78U, 0x15U, 0x94U, 0x72U, 0x38U, 0xE3U, 0xF5U};
    uint8_t keyBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x31U};
    uint8_t ivrBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x32U};
    uint8_t dataOut[16] = {0x00};
    uint32_t dataOutLen;
    const uint8_t scrResultBuf[16] = {0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x30U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    int32_t result;
    FL_ErrorStatus status;
    /********************解密过程********************/
    status = AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 16, dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, 16);

    if(result != 0) { return FL_FAIL; }

    return FL_PASS;

}

/**
  * @brief  AES的CTR模式加密测试程序
  * @param  void
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */

FL_ErrorStatus AES_CTR_Encrypt(void)
{
    uint8_t dataInBuf[16] = {0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x30U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    uint8_t keyBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x31U};
    uint8_t ivrBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x32U};
    uint8_t dataOut[16] = {0x00};
    uint32_t dataOutLen;
    const uint8_t scrResultBuf[16] = {0xDCU, 0xCAU, 0xB2U, 0x5EU, 0x5CU, 0xCAU, 0xFAU, 0x88U, 0xC1U, 0x8BU, 0xFFU, 0x1BU, 0x3DU, 0xD8U, 0x4AU, 0x97U};
    int32_t result;
    FL_ErrorStatus status;
    /********************加密过程********************/
    status = AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 16, dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, 16);
    if(result != 0) { return FL_FAIL; }

    return FL_PASS;

}

/**
  * @brief  AES的CTR模式解密测试程序
  * @param  void
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */

FL_ErrorStatus AES_CTR_Decrypt(void)
{
    uint8_t dataInBuf[16] = {0xDCU, 0xCAU, 0xB2U, 0x5EU, 0x5CU, 0xCAU, 0xFAU, 0x88U, 0xC1U, 0x8BU, 0xFFU, 0x1BU, 0x3DU, 0xD8U, 0x4AU, 0x97U};
    uint8_t keyBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x31U};
    uint8_t ivrBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x32U};
    uint8_t dataOut[16] = {0x00};
    uint32_t dataOutLen;
    const uint8_t scrResultBuf[16] = {0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x30U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    int32_t result;
    FL_ErrorStatus status;
    /********************解密过程********************/
    status = AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 16, dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, 16);
    if(result != 0) { return FL_FAIL; }

    return FL_PASS;

}

/**
  * @brief  AES的CBC模式加密测试程序
  * @param  void
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */

FL_ErrorStatus AES_CBC_Encrypt(void)
{
    uint8_t dataInBuf[16] = {0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x30U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    uint8_t keyBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x31U};
    uint8_t ivrBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x32U};
    uint8_t dataOut[16] = {0x00};
    uint32_t dataOutLen;
    const uint8_t scrResultBuf[16] = {0x62U, 0xAAU, 0xA1U, 0x85U, 0xECU, 0xFBU, 0x83U, 0x39U, 0xABU, 0x9EU, 0x11U, 0x7AU, 0xAAU, 0xFDU, 0x79U, 0x68U};
    int32_t result;
    FL_ErrorStatus status;
    /********************加密过程********************/
    status = AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 16, dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, 16);
    if(result != 0) { return FL_FAIL; }

    return FL_PASS;

}

/**
  * @brief  AES的CBC模式解密测试程序
  * @param  void
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */

FL_ErrorStatus AES_CBC_Decrypt(void)
{
    uint8_t dataInBuf[16] = {0x62U, 0xAAU, 0xA1U, 0x85U, 0xECU, 0xFBU, 0x83U, 0x39U, 0xABU, 0x9EU, 0x11U, 0x7AU, 0xAAU, 0xFDU, 0x79U, 0x68U};
    uint8_t keyBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x31U};
    uint8_t ivrBuf[16] = {0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x30U, 0x32U};
    uint8_t dataOut[16] = {0x00};
    uint32_t dataOutLen;
    const uint8_t scrResultBuf[16] = {0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U, 0x30U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};
    int32_t result;
    FL_ErrorStatus status;
    /********************解密过程********************/
    status = AES_EncryptionAndDecryption(keyBuf, 16, ivrBuf, dataInBuf, 16, dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, 16);
    if(result != 0) { return FL_FAIL; }

    return FL_PASS;
}


/**
  * @brief  AES的MULTH模式测试程序
  * @param  void
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 测试成功
  *         -FL_FAIL 测试失败
  */

FL_ErrorStatus AES_MULTH(void)
{
    uint32_t dataInBuf[40] =
    {
        0xb41daef8U, 0xe7d02b66U, 0x9061a816U, 0x6a317b9eU,
        0x434cbdbaU, 0x78fe5268U, 0x0dd73ba7U, 0x3cd2e070U,
        0x4ba4511bU, 0x58ea7aa3U, 0xc87b8419U, 0xa98756bfU,
        0x4c217832U, 0xa58a98caU, 0x5ca90d2dU, 0x56c29ea1U,
        0xa4a583e6U, 0x109e5b42U, 0x86f49998U, 0x42b1c6cfU,
        0x61c9895bU, 0x5d5cc16eU, 0x65adc8bbU, 0x7d7ec242U,
        0x817fad74U, 0x3ebea341U, 0x143ae52cU, 0x7aa6aa83U,
        0x8b6bae55U, 0x60a85675U, 0x322e7b50U, 0x95ad2998U,
        0x7f3890adU, 0x6719d313U, 0xab975a8aU, 0x2aaec3e3U,
        0x30549636U, 0x2c2ab020U, 0xc1a7c503U, 0xb8db2fb0U
    };
    uint32_t hbuf[4] =
    {
        0xa7121942U, 0x8e9a431aU, 0x87deb4abU, 0x9cea030eU
    };

    uint32_t ivrBuf[4] =
    {
        0x7c776dd9U, 0x444bccc4U, 0xc9367885U, 0x4be99b67U
    };

    uint32_t scrResultBuf[40] =
    {
        0xc26d7314U, 0x7ef12993U, 0x7924d021U, 0x49a288bdU,
        0xb8074a26U, 0x6080b4efU, 0x9dd6f65cU, 0xa1316074U,
        0xe64ce340U, 0x69d9e114U, 0x22f96a6fU, 0xa9e6b908U,
        0x0bfe4c53U, 0x87ebab8aU, 0x3caf1e52U, 0x6c7779e0U,
        0xb0ad8400U, 0x174fe560U, 0x052640e8U, 0x67ad35a1U,
        0x35478633U, 0x03653c71U, 0x1fcec3e7U, 0x047e32cdU,
        0x3cb75b8eU, 0x9102fcc4U, 0xfdc594e5U, 0xc7f52620U,
        0x674bd35dU, 0x6ea2885fU, 0x70efa246U, 0x4304712dU,
        0x1a1a0bb7U, 0xadff3ae5U, 0x7ce6ae15U, 0xaaf7e174U,
        0xd0287e4dU, 0x531de812U, 0x22ab2933U, 0x50173ddbU
    };

    uint32_t dataOut[40];
    uint32_t dataOutLen;
    int32_t result;
    FL_ErrorStatus status;

    ByteExChange(dataInBuf, 40);
    ByteExChange(hbuf, 4);
    ByteExChange(ivrBuf, 4);
    ByteExChange(scrResultBuf, 40);

    status = AES_EncryptionAndDecryption((uint8_t *)hbuf, 16, (uint8_t *)ivrBuf, (uint8_t *)dataInBuf, 40 * 4, (uint8_t *)dataOut, &dataOutLen);
    if(status == FL_FAIL) { return FL_FAIL; }

    result = strncmp((const char *)dataOut, (const char *)scrResultBuf, (size_t)(40 * 4));
    if(result != 0) { return FL_FAIL; }

    return FL_PASS;

}

