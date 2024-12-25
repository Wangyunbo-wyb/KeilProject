#include "aes.h"
#include "aes_gcm.h"
#include <string.h>

typedef enum
{
    /* 加密模式 */
    ENCRYPT,
    /* 解密模式*/
    DECRYPT
} CRYPT;

/**
  * @brief  uint32_t类型数据小端转为大端
  * @param  datatemp 输入参数：待交换数据
  * @param  buf 输出参数：输出指针地址
  * @retval None
  */
__STATIC_INLINE void int2Byte_MSB(uint32_t datatemp, uint8_t *buf)
{
    buf[3] = (uint8_t)datatemp;
    buf[2] = (uint8_t)(datatemp >> 8);
    buf[1] = (uint8_t)(datatemp >> 16);
    buf[0] = (uint8_t)(datatemp >> 24);
}

/**
  * @brief  uint32_t类型数据Bit交换
  * @param  n 输入参数：待交换数据
  * @param  buf 输出参数：输出指针地址
  * @retval 返回值：Bit交换之后的值
  */
static uint32_t revBits(uint32_t n)
{
    n = ((n >> 1) & 0x55555555U) | ((n << 1) & 0xaaaaaaaaU);
    n = ((n >> 2) & 0x33333333U) | ((n << 2) & 0xccccccccU);
    n = ((n >> 4) & 0x0f0f0f0fU) | ((n << 4) & 0xf0f0f0f0U);
    n = ((n >> 8) & 0x00ff00ffU) | ((n << 8) & 0xff00ff00U);
    n = ((n >> 16) & 0x0000ffffU) | ((n << 16) & 0xffff0000U);
    return n;
}

/**
  * @brief  128bit数据进行倒叙
  * @param  bufIn 输入参数：待交换的数据指针地址
  * @param  bufOut 输出参数：交换后的数据指针地址
  * @retval None
  */
static void BitExchange128(uint32_t *bufOut, uint32_t *bufIn)
{
    uint32_t    temp;

    temp = revBits(bufIn[0]);
    bufOut[0] = revBits(bufIn[3]);
    bufOut[3] = temp;
    temp = revBits(bufIn[1]);
    bufOut[1] = revBits(bufIn[2]);
    bufOut[2] = temp;

}
/**
  * @brief  检查计算完成标志
  * @param  None
  * @retval FL_FlagStatus枚举型
  *         -FL_RESET 未检测到计算完成标志
  *         -FL_SET 检测到计算完成标志
  */
static FL_FlagStatus AES_Cal_Finished_Flag_Chk(void)
{
    int i;

    for(i = 0; i < 500; i++)
    {
        if(0X01 == FL_AES_IsActiveFlag_Complete(AES)) { break; }
    }

    if(i == 500) { return FL_RESET; }

    FL_AES_ClearFlag_Complete(AES);
    return FL_SET;
}

/**
  * @brief  启动Multh计算
  * @param  hParams Multh参数指针地址
  * @retval int数据类型
  *         -0 成功
  *         -其他 失败
  */
static int aes_multStart(uint8_t *hParams)
{
    uint32_t    buf[4];
    FL_ErrorStatus result;
    /* AES 初始化 */
    result = AES_Init(FL_AES_KEY_LENGTH_128B, FL_AES_CIPHER_MULTH, FL_AES_OPERATION_MODE_ENCRYPTION, FL_AES_DATA_TYPE_32B);
    /* 返回失败 */
    if(result == FL_FAIL) {return -1;}

    memcpy((void *)buf, (const void *)hParams, 16);
    /* 128Bit倒叙 */
    BitExchange128(buf, buf);
    /* 设置Multh参数寄存器 */
    AES_H_WriteEx((uint8_t *) buf);
    memset((void *)buf, 0, 16);
    /* 设置IVR参数寄存器 */
    AES_IVR_WriteEx((uint8_t *) buf);
    /* 启动AES */
    FL_AES_Enable(AES);

    /* 返回成功 */
    return 0;
}

/**
  * @brief  Multh计算
  * @param  in 待Multh计算的数据指针地址
  * @param  len 待Multh计算的数据指长度
  * @retval int数据类型
  *         -0 成功
  *         -其他 失败
  */
static int aes_multUpdate(uint8_t *in, uint32_t len)
{
    uint32_t    buf[4];
    uint32_t    i;

    /* hash长度为0，直接返回成功 */
    if(len == 0) { return 0; }

    /* in 为 NULL，直接返回失败 */
    if(in == NULL) { return -1; }

    for(i = 0; i < len; i += 16)
    {
        /* in地址的数据copy到buf */
        if(len - i < 16)
        {
            memmove((void *)buf, (const void *)in, (size_t)(len - i));
        }
        else
        {
            memmove((void *)buf, (const void *)in, (size_t)16);
        }
        /* 将buf数据进行128Bit倒叙 */
        BitExchange128(buf, buf);

        if(len - i < 16)
        {
            /* 不足16字节补零 */
            memset((void *)buf, 0, (size_t)(16 - (len - i)));
        }

        /* AES 计算 */
        AES_DIN_GroupWrite_128BIT((uint8_t *) buf);

        /* 等待CCF标志置起,完成计算大约需要100个时钟周期 */
        if(FL_RESET == AES_Cal_Finished_Flag_Chk()) { return -1; }

        if(len - i < 16)
        {
            in += (len - i);
        }
        else
        {
            in += 16;
        }
    }

    return 0;
}

/**
  * @brief  Multh计算完成
  * @param  out 输出参数：AES计算结果输出指针地址
  * @param  len 输入参数：数据长度(固定取16字节)
  * @retval None
  */
static void aes_multfinish(uint8_t *out, uint32_t len)
{
    uint32_t    outBuf[4];

    /* out 为 NULL，直接返回 */
    if(out == NULL) { return ; }

    AES_IVR_ReadEx((uint8_t *) outBuf);
    FL_AES_Disable(AES);//重置AES模块
    BitExchange128(outBuf, outBuf);
    memcpy((void *)out, (const void *)outBuf, (size_t)len);
}

/**
  * @brief  CTR模式初始化
  * @param  crypt 加解密模式
  * @param  key 秘钥指针地址
  * @param  keyLen 秘钥长度
  * @param  iv 初始向量指针地址
  * @retval int数据类型
  *         -0 成功
  *         -其他 失败
  */
static int aes_CTRInit(CRYPT crypt, uint8_t *key, uint32_t keyLen, uint8_t *iv)
{
    FL_AES_InitTypeDef AES_InitStruct;
    FL_ErrorStatus status;
    /* key 或者  iv为 NULL，直接返回失败 */
    if((key == NULL) || (iv == NULL)) { return -1; }

    if((keyLen != 16) && (keyLen != 24) && (keyLen != 32)) { return -1; }

    memset((void *)(&AES_InitStruct), 0, (size_t)(sizeof(AES_InitStruct)));
    /***************加密测试********************/
    /* 重置AES模块 */
    FL_AES_Disable(AES);
    /* AES数据流处理模式 */
    AES_InitStruct.cipherMode = FL_AES_CIPHER_CTR;
    /* 数据寄存器数据交换 */
    AES_InitStruct.dataType = FL_AES_DATA_TYPE_32B;

    switch(keyLen)
    {
        /* 128bit */
        case 16:
            /* AES加密密钥长度 */
            AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_128B;
            break;
        /* 192bit */
        case 24:
            AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_192B;
            break;
        /* 256bit */
        case 32:
            AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_256B;
            break;

        default:
            /* 不应走到此处 */
            break;
    }

    /* AES工作模式 */
    if(crypt == ENCRYPT)
    {
        /* 加密 */
        AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
    }

    else
    {
        /* 解密 */
        AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
    }

    /* AES初始化*/
    status = FL_AES_Init(AES, &AES_InitStruct);
    if(status == FL_FAIL) { return -1; }

    /* 设置密钥*/
    AES_KEY_WriteEx(key, keyLen);

    /* CTR和CBC模式下写AES_IVRx寄存器 */
    AES_IVR_WriteEx(iv);
    return 0;
}

/**
  * @brief  AES CTR进行加解密
  * @param  in 输入参数：待加解密数据指针地址
  * @param  inLen 输入参数：待加密数据长度
  * @param  out 输出参数：加解密数据指针地址
  * @param  outLen 输出参数：加解密数据长度
  * @param  ctrMod 输入参数：ctrMod=0,32位CTR,否则128bit
  * @retval 返回值：0成功，否则失败
  */
static int aes_Crypt(uint8_t *in, uint32_t inLen, uint8_t *out, int32_t ctrMod)
{
    FL_ErrorStatus  result;
    uint64_t counter;
    uint8_t     Buf[16];
    uint8_t     BufB[16];
    uint32_t    i;
    counter = AES->IVR0;

    if(inLen == 0) { return 0; }

    if((in == NULL) || (out == NULL)) { return -1; }

    /* 启动AES*/
    FL_AES_Enable(AES);

    /* 加密数据*/
    for(i = 0; i < (inLen / 16); i++)
    {
        /* 每128Bit进行数据处理 */
        result = AES_GroupWriteAndRead_128BIT(in + i * 16, out + i * 16);
        if(result == FL_FAIL) { return -1; }

        if(ctrMod != 0)
        {
            /* counter 32Bit溢出处理 */
            counter++;

            if(counter > 0xFFFFFFFFU)
            {
                FL_AES_Disable(AES);
                counter = (uint64_t)AES->IVR1 + 1;

                if(counter > 0xFFFFFFFFU)
                {
                    AES->IVR1 = 0;
                    counter = (uint64_t)AES->IVR2 + 1;

                    if(counter > 0xFFFFFFFFU)
                    {
                        AES->IVR2 = 0;
                        counter = (uint64_t)AES->IVR3 + 1;

                        if(counter > 0xFFFFFFFFU)
                        {
                            AES->IVR3 = 0;
                        }
                    }
                }

                counter = 0;
                FL_AES_Enable(AES);
            }
        }
    }

    /* 不足16字节进行补零操作 */
    if((inLen % 16) != 0)
    {
        memset((void *)Buf, 0, 16);
        memcpy((void *)Buf, (const void *)(in + i * 16), (size_t)(inLen - i * 16));
        result = AES_GroupWriteAndRead_128BIT(Buf, BufB);
        if(result == FL_FAIL) { return -1; }

        memcpy((void *)(out + i * 16), (const void *)BufB, (size_t)(inLen - i * 16));
    }

    /* 关闭AES模块 */
    FL_AES_Disable(AES);
    return 0;
}

/**
  * @brief  AES ECB模式初始化
  * @param  crypt 输入参数：加解密模式
  * @param  key 输入参数：秘钥指针地址
  * @param  keyLen 输入参数：秘钥长度
  * @retval 返回值
  *         -0 初始化成功
  *         -其他 失败
  */
static int aes_ECBInit(CRYPT crypt, uint8_t *key, uint32_t keyLen)
{
    FL_AES_InitTypeDef AES_InitStruct;
    FL_ErrorStatus status;
    if(key == NULL) { return -1; }

    if((keyLen != 16) && (keyLen != 24) && (keyLen != 32)) { return -1; }

    memset((void *)(&AES_InitStruct), 0, (size_t)(sizeof(AES_InitStruct)));
    /* AES数据流处理模式 */
    AES_InitStruct.cipherMode = FL_AES_CIPHER_ECB;
    /* 数据寄存器交换 */
    AES_InitStruct.dataType = FL_AES_DATA_TYPE_32B;

    switch(keyLen)
    {
        /* 128bit */
        case 16:
            /* AES加密密钥长度*/
            AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_128B;
            break;

        /* 192bit */
        case 24:
            AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_192B;
            break;

        /* 256bit */
        case 32:
            AES_InitStruct.keyLength = FL_AES_KEY_LENGTH_256B;
            break;

        default:
            /* 不应走到此处 */
            break;
    }

    /* AES工作模式 */
    if(crypt == ENCRYPT)
    {
        /* 加密模式 */
        AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_ENCRYPTION;
    }

    else
    {
        /* 解密模式 */
        AES_InitStruct.operationMode = FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION;
    }

    /* 初始化AES */
    status = FL_AES_Init(AES, &AES_InitStruct);
    if(status == FL_FAIL)   {return -1;}

    /* 设置密钥 */
    AES_KEY_WriteEx(key, keyLen);
    return 0;
}


/**
  * @brief  GCM HASH计算
  * @param  hParams 输入参数：H参数指针地址
  * @param  aadBuf 输入参数：附加信息域指针地址
  * @param  aadBufLen 输入参数：附加信息域长度
  * @param  ct 输入参数：待加密数据指针地址
  * @param  ctLen 输入参数：待加密长度
  * @param  tag 输入参数：Tag指针地址
  * @param  tagLen 输入参数：Tag数据长度
  * @retval 返回值
  *         -0 成功
  *         -其他 失败
  */
static int gcm_hash(uint8_t *hParams, uint8_t *aadBuf, uint32_t aadBufLen, uint8_t *ct, uint32_t ctLen,
                    uint8_t *tag, uint32_t tagLen)
{
    uint32_t    buff[4];
    int result;

    if(hParams != NULL)
    {
        result = aes_multStart(hParams);
        if(result != 0)     { return -1; }
    }

    if(aadBuf != NULL)
    {
        result = aes_multUpdate(aadBuf, aadBufLen);
        if(result != 0)     { return -1; }
    }

    if(ct != NULL)
    {
        result = aes_multUpdate(ct, ctLen);
        if(result != 0)     { return -1; }
    }

    memset((void *)buff, 0, 16);
    int2Byte_MSB((aadBufLen << 3), (uint8_t *)(buff + 1));
    int2Byte_MSB((ctLen << 3), (uint8_t *)(buff + 3));

    result = aes_multUpdate((uint8_t *) buff, 16);
    if(result != 0)     { return -1; }

    aes_multfinish((uint8_t *) buff, 16);

    if(tag == NULL) { return -1; }
    /* 输出Tag */
    memcpy((void *)tag, (const void *)buff, (size_t)tagLen);
    /* 返回正确*/
    return 0;
}

/**
  * @brief  GCM 加密计算
  * @param  key 输入参数：秘钥指针地址
  * @param  keyLen 输入参数：秘钥长度
  * @param  ivrBuf 输入参数：iv向量指针地址
  * @param  ivLen 输入参数：iv数据长度
  * @param  aadBuf 输入参数：附加信息域指针地址
  * @param  aadBufLen 输入参数：附加信息域长度
  * @param  pt 输入参数：明文数据指针地址
  * @param  ptLen 输入参数：明文数据长度
  * @param  ct 输出参数：密文数据指针地址
  * @param  ctLen 输入参数：密文数据长度
  * @param  tag 输出参数：Tag指针地址
  * @param  tagLen 输入参数：Tag数据长度
  * @retval 返回值
  *         -0 成功
  *         -其他 失败
  */
int gcm_AEk(uint8_t *key, uint32_t keyLen, uint8_t *ivrBuf, uint32_t ivLen, uint8_t *aadBuf,
            uint32_t aadBufLen, uint8_t *pt, uint32_t ptLen, uint8_t *ct, uint32_t ctLen, uint8_t *tag,
            uint32_t tagLen)
{
    uint32_t    subKey[4];
    uint32_t    J0[4];
    uint32_t    hash[4];
    int32_t     result;
    /* 第一步，使用key对128bit的零进行ECB加密，得到subKey H */
    memset((void *)subKey, 0, (size_t)(sizeof(subKey)));
    result = aes_ECBInit(ENCRYPT, key, keyLen);
    if(result != 0) { return -1; }

    result = aes_Crypt((uint8_t *) subKey, sizeof(subKey), (uint8_t *) subKey, 0);
    if(result != 0) { return -1; }

    /* 第二步，获得前计数块 Y0或J0 */
    if(ivLen == (96 / 8))
    {
        /* 1、如果IV=96,则IV||COUNTER,COUNTER=1 */
        memcpy((void *)J0, (const void *)ivrBuf, 12);
        /* 下一次使用时需要counter+1 */
        J0[3]       = 0x01000000U;
    }

    else
    {
        /* 2、否则GHASH(subkey,null,IV) */
        result = gcm_hash((uint8_t *) subKey, NULL, 0, ivrBuf, ivLen, (uint8_t *) J0, 16);
        if(result != 0) { return -1; }
    }

    J0[3]       = (uint32_t)__REV(__REV(J0[3]) + 1);

    /* 第三步、对明文 P 异或 CTR加密的Yi，得到密文 C */
    if(ptLen != 0)
    {
        result = aes_CTRInit(ENCRYPT, key, keyLen, (uint8_t *) J0);
        if(result != 0) { return -1; }

        result = aes_Crypt(pt, ptLen, ct, 0);
        if(result != 0) { return -1; }
    }

    /* 第四步、依次对 a补零的附加信息域A、密文C、len(A)||len(C)模乘第一步的subkey H */
    result = gcm_hash((uint8_t *) subKey, aadBuf, aadBufLen, ct, ctLen, (uint8_t *) hash, sizeof(hash));
    if(result != 0) { return -1; }

    /* 第五步、以key为密码,Y0/J0为IV，对第五步的GHASH值进行CTR加密，然后bit交换为大端，即可得到身份标签 tag */
    J0[3]       = (uint32_t)__REV(__REV(J0[3]) - 1);
    result = aes_CTRInit(ENCRYPT, key, keyLen, (uint8_t *) J0);
    if(result != 0) { return -1; }

    result = aes_Crypt((uint8_t *) hash, sizeof(hash), (uint8_t *) hash, 0);
    if(result != 0) { return -1; }

    if(tag == NULL) { return -1; }
    memcpy((void *)tag, (const void *)hash, (size_t)tagLen);

    return 0;
}

/**
  * @brief  GCM 解密计算
  * @param  key 输入参数：秘钥指针地址
  * @param  keyLen 输入参数：秘钥长度
  * @param  ivrBuf 输入参数：iv向量指针地址
  * @param  ivLen 输入参数：iv数据长度
  * @param  aadBuf 输入参数：附加信息域指针地址
  * @param  aadBufLen 输入参数：附加信息域长度
  * @param  ct 输入参数：密文数据指针地址
  * @param  ctLen 输入参数：密文数据长度
  * @param  pt 输出参数：明文数据指针地址
  * @param  ptLen 输入参数：明文数据长度
  * @param  tag 输入参数：Tag指针地址
  * @param  tagLen 输入参数：Tag数据长度
  * @retval 返回值
  *         -0 成功
  *         -其他 失败
  */
int gcm_ADk(uint8_t *key, uint32_t keyLen, uint8_t *ivrBuf, uint32_t ivLen, uint8_t *aadBuf,
            uint32_t aadBufLen, uint8_t *ct, uint32_t ctLen, uint8_t *pt, uint32_t ptLen, uint8_t *tag,
            uint32_t tagLen)
{
    uint32_t    tagTemp[4];
    uint32_t    subKey[4];
    uint32_t    J0[4];
    int32_t  result;

    /* 第一步，使用key对128bit的零进行ECB加密，得到subKey H */
    memset((void *)subKey, 0, (size_t)(sizeof(subKey)));
    result = aes_ECBInit(ENCRYPT, key, keyLen);
    if(result != 0) { return -1; }

    result = aes_Crypt((uint8_t *) subKey, sizeof(subKey), (uint8_t *) subKey, 0);
    if(result != 0) { return -1; }

    /* 第二步，获得前计数块 Y0或J0 */
    if(ivLen == (96 / 8))
    {
        /* 1、如果IV=96,则IV||COUNTER,COUNTER=1 */
        memcpy((void *)J0, (const void *)ivrBuf, 12);
        /* 下一次使用时需要counter+1 */
        J0[3]       = 0x01000000U;
    }

    else
    {
        /* 2、否则GHASH(subkey,null,IV) */
        result = gcm_hash((uint8_t *) subKey, NULL, 0, ivrBuf, ivLen, (uint8_t *) J0, 16);
        if(result != 0) { return -1; }
    }

    /* 第四步、依次对 a补零的附加信息域A、密文C、len(A)||len(C)模乘第一步的subkey H */
    result = gcm_hash((uint8_t *) subKey, aadBuf, aadBufLen, ct, ctLen, (uint8_t *) tagTemp, 16);
    if(result != 0) { return -1; }

    /* 第五步、以key为密码,Y0/J0为IV，对第五步的GHASH值进行CTR加密，然后bit交换为大端，即可得到身份标签 tag */
    result = aes_CTRInit(ENCRYPT, key, keyLen, (uint8_t *) J0);
    if(result != 0) { return -1; }

    result = aes_Crypt((uint8_t *)tagTemp, 16, (uint8_t *)tagTemp, 0);
    if(result != 0) { return -1; }

    /* Tag比较 */
    if(strncmp((const char *)tagTemp, (const char *)tag, (size_t)tagLen) != 0)
    {
        return -1;
    }

    /* 第三步、对明文 P 异或 CTR加密的Yi，得到密文 C */
    J0[3]       = (uint32_t)__REV(__REV(J0[3]) + 1);
    result = aes_CTRInit(ENCRYPT, key, keyLen, (uint8_t *) J0);
    if(result != 0) { return -1; }

    result = aes_Crypt(ct, ctLen, pt, 0);
    if(result != 0) { return -1; }
    return 0;
}

/**
  * @note   keyBuf的数组改成16字节数组，秘钥长度输入设置为128Bit
  * @brief  GCM128 IV数据长度为96Bit的加密签名解密验签计算
  * @param  void
  * @retval 返回值
  *         -FL_PASS 成功
  *         -其他 失败
  */
FL_ErrorStatus AES_IV_96Bit_GCM128Bit(void)
{
    int result = -1;
    uint8_t encryptInBuf[13] = {0xC0U, 0x01U, 0x00U, 0x00U, 0x08U, 0x00U, 0x00U, 0x01U, 0x00U, 0x00U, 0xFFU, 0x02U, 0x00U};
    uint8_t aadBuf[17] = {0x30U, 0xD0U, 0xD1U, 0xD2U, 0xD3U, 0xD4U, 0xD5U, 0xD6U, 0xD7U, 0xD8U, 0xD9U, 0xDAU, 0xDBU, 0xDCU, 0xDDU, 0xDEU, 0xDFU};
    uint8_t keyBuf[16] = {0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU};
    uint8_t ivrBuf[12] = {0x4DU, 0x4DU, 0x4DU, 0x00U, 0x00U, 0xBCU, 0x61U, 0x4EU, 0x01U, 0x23U, 0x45U, 0x67U};
    /* const uint8_t scrTag[12] = {0x7dU, 0x82U, 0x5cU, 0x3bU, 0xe4U, 0xa7U, 0x7cU, 0x3fU, 0xccU, 0x05U, 0x6bU, 0x6bU}; */

    uint8_t EncryptBuf[16];
    uint8_t Tag[16];
    uint8_t DecryptBuf[16];

    /* 加密签名 */
    result = gcm_AEk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));
    if(result != 0) { return FL_FAIL; }

    /* 解密验签 */
    result = gcm_ADk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));

    if(result != 0) { return FL_FAIL; }

    return FL_PASS;
}

/**
  * @note   keyBuf的数组改成16字节数组，秘钥长度输入设置为128Bit
  * @brief  GCM128 IV数据长度为不满96Bit的加密签名解密验签计算
  * @param  void
  * @retval 返回值
  *         -FL_PASS 成功
  *         -其他 失败
  */
FL_ErrorStatus AES_IV_Not96Bit_GCM128Bit(void)
{
    int result = -1;
    uint8_t encryptInBuf[16] = {0x2DU, 0x4DU, 0x25U, 0x20U, 0x77U, 0x62U, 0x6CU, 0xDEU, 0x15U, 0x1DU, 0xBEU, 0x3FU, 0x4BU, 0x7EU, 0xA2U, 0xE4U};
    uint8_t aadBuf[16] = {0xCCU, 0x9FU, 0xB0U, 0x86U, 0x87U, 0x42U, 0x7CU, 0x57U, 0x04U, 0x2EU, 0x36U, 0x9BU, 0x28U, 0x6EU, 0x4DU, 0x5AU};
    uint8_t keyBuf[16] = {0x59U, 0x50U, 0x45U, 0x55U, 0xADU, 0x1FU, 0x96U, 0xDFU, 0x17U, 0x1EU, 0xDFU, 0xC3U, 0x06U, 0x5BU, 0xD3U, 0x6DU};
    uint8_t ivrBuf[1] = {0xCAU};
    /* const uint8_t scrTag[4] = {0x1FU, 0x52U, 0x05U, 0x82U}; */

    uint8_t EncryptBuf[16];
    uint8_t Tag[16];
    uint8_t DecryptBuf[16];

    /* 加密签名 */
    result = gcm_AEk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));
    if(result != 0) { return FL_FAIL; }

    /* 解密验签 */
    result = gcm_ADk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));

    if(result != 0) { return FL_FAIL; }

    return FL_PASS;
}

/**
  * @note   keyBuf的数组改成32字节数组，秘钥长度输入设置为256Bit
  * @brief  GCM256 IV数据长度为96Bit的加密签名解密验签计算
  * @param  void
  * @retval 返回值
  *         -FL_PASS 成功
  *         -其他 失败
  */
FL_ErrorStatus AES_IV_96Bit_GCM256Bit(void)
{
    int result = -1;
    uint8_t encryptInBuf[13] = {0xC0U, 0x01U, 0x00U, 0x00U, 0x08U, 0x00U, 0x00U, 0x01U, 0x00U, 0x00U, 0xFFU, 0x02U, 0x00U};
    uint8_t aadBuf[17] = {0x30U, 0xD0U, 0xD1U, 0xD2U, 0xD3U, 0xD4U, 0xD5U, 0xD6U, 0xD7U, 0xD8U, 0xD9U, 0xDAU, 0xDBU, 0xDCU, 0xDDU, 0xDEU, 0xDFU};
    uint8_t keyBuf[32] = {0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU, 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU};
    uint8_t ivrBuf[12] = {0x4DU, 0x4DU, 0x4DU, 0x00U, 0x00U, 0xBCU, 0x61U, 0x4EU, 0x01U, 0x23U, 0x45U, 0x67U};
    /* const uint8_t scrTag[12] = {0xD5U, 0xB6U, 0xD5U, 0x12U, 0xEEU, 0x23U, 0xBBU, 0x5DU, 0xE3U, 0x40U, 0x65U, 0x23U}; */

    uint8_t EncryptBuf[16];
    uint8_t Tag[16];
    uint8_t DecryptBuf[16];

    /* 加密签名 */
    result = gcm_AEk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));
    if(result != 0) { return FL_FAIL; }

    /* 解密验签 */
    result = gcm_ADk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));

    if(result != 0) { return FL_FAIL; }

    return FL_PASS;
}

/**
  * @note   keyBuf的数组改成24字节数组，秘钥长度输入设置为192Bit
  * @brief  GCM192 IV数据长度为96Bit的加密签名解密验签计算
  * @param  void
  * @retval 返回值
  *         -FL_PASS 成功
  *         -其他 失败
  */
FL_ErrorStatus AES_IV_96Bit_GCM192Bit(void)
{
    int result = -1;
    uint8_t encryptInBuf[13] = {0xC0U, 0x01U, 0x00U, 0x00U, 0x08U, 0x00U, 0x00U, 0x01U, 0x00U, 0x00U, 0xFFU, 0x02U, 0x00U};
    uint8_t aadBuf[17] = {0x30U, 0xD0U, 0xD1U, 0xD2U, 0xD3U, 0xD4U, 0xD5U, 0xD6U, 0xD7U, 0xD8U, 0xD9U, 0xDAU, 0xDBU, 0xDCU, 0xDDU, 0xDEU, 0xDFU};
    uint8_t keyBuf[24] = {0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U, 0x08U, 0x09U, 0x0AU, 0x0BU, 0x0CU, 0x0DU, 0x0EU, 0x0FU, 0x00U, 0x01U, 0x02U, 0x03U, 0x04U, 0x05U, 0x06U, 0x07U};
    uint8_t ivrBuf[12] = {0x4DU, 0x4DU, 0x4DU, 0x00U, 0x00U, 0xBCU, 0x61U, 0x4EU, 0x01U, 0x23U, 0x45U, 0x67U};
    /* const uint8_t scrTag[12] = {0x76U, 0xF2U, 0x3DU, 0xE8U, 0x5AU, 0x54U, 0x24U, 0x04U, 0x05U, 0xB7U, 0x14U, 0x5DU}; */

    uint8_t EncryptBuf[16];
    uint8_t Tag[16];
    uint8_t DecryptBuf[16];

    /* 加密签名 */
    result = gcm_AEk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), encryptInBuf, sizeof(encryptInBuf), EncryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));
    if(result != 0) { return FL_FAIL; }

    /* 解密验签 */
    result = gcm_ADk(keyBuf, sizeof(keyBuf), ivrBuf, sizeof(ivrBuf), aadBuf, sizeof(aadBuf), EncryptBuf, sizeof(encryptInBuf), DecryptBuf, sizeof(encryptInBuf), Tag, sizeof(Tag));

    if(result != 0) { return FL_FAIL; }

    return FL_PASS;
}
