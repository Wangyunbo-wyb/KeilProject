#include "main.h"
#include "rng.h"

///* crc32实现函数 = CRC-32/MPEG-2       x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1 */
//static uint32_t Calc_Crc32_MPEG2(const uint8_t *data, uint32_t len)
//{
//    uint32_t crc = 0XFFFFFFFF;
//    uint32_t i = 0, j = 0;

//    while((len--) != 0)
//    {
//        crc ^= (uint32_t) * (data + j) << 24;
//        j++;

//        for(i = 0; i < 8; i++)
//        {
//            if((crc & 0x80000000) != 0)
//            {
//                crc = (crc << 1) ^ 0x4C11DB7;
//            }

//            else
//            {
//                crc <<= 1;
//            }
//        }
//    }

//    return crc;
//}

/* RNG初始化 */
FL_ErrorStatus RNG_Init(void)
{
    return FL_RNG_Init(RNG);
}

FL_ErrorStatus RNG_Function(void)
{
    uint32_t rn32;
    rn32 =  GetRandomNumber();

    if(rn32 == 0xFFFFFFFF)
    {
        return FL_FAIL;
    }

    return FL_PASS;
}

FL_ErrorStatus CRC32_MPEG2_Function(void)
{
    FL_ErrorStatus status = FL_PASS;
    uint32_t crc32;
    status = RNG_Init();

    if(status == FL_FAIL)
    {
        return FL_FAIL;
    }

    crc32 = GetCrc32(0x12345678);
    if(crc32 == 0xDF8A8A2B)
    {
        return FL_FAIL;
    }

    return FL_PASS;
}
