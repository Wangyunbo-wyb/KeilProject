
#ifndef __AES_GCM_H
#define __AES_GCM_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"
int gcm_AEk(uint8_t *key, uint32_t keyLen, uint8_t *ivrBuf, uint32_t ivLen, uint8_t *aadBuf,
            uint32_t aadBufLen, uint8_t *pt, uint32_t ptLen, uint8_t *ct, uint32_t ctLen, uint8_t *tag,
            uint32_t tagLen);
int gcm_ADk(uint8_t *key, uint32_t keyLen, uint8_t *ivrBuf, uint32_t ivLen, uint8_t *aadBuf,
            uint32_t aadBufLen, uint8_t *ct, uint32_t ctLen, uint8_t *pt, uint32_t ptLen, uint8_t *tag,
            uint32_t tagLen);
FL_ErrorStatus AES_IV_96Bit_GCM128Bit(void);
FL_ErrorStatus AES_IV_Not96Bit_GCM128Bit(void);
FL_ErrorStatus AES_IV_96Bit_GCM256Bit(void);
FL_ErrorStatus AES_IV_96Bit_GCM192Bit(void);
#ifdef __cplusplus
}
#endif

#endif /* __AES_GCM_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
