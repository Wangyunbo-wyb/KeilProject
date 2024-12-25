#ifndef __AES_H
#define __AES_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

void AES_H_WriteEx(uint8_t *hxIn);
void AES_H_ReadEx(uint8_t *hxOut);
void AES_KEY_WriteEx(uint8_t *keyIn, uint32_t len);
void AES_KEY_ReadEx(uint8_t *keyOut, uint32_t len);
void AES_IVR_WriteEx(uint8_t *ivrIn);
void AES_IVR_ReadEx(uint8_t *ivrOut);
void AES_DIN_GroupWrite_128BIT(uint8_t *dataIn);
void AES_DOUT_GroupRead_128BIT(uint8_t *dataOut);
FL_ErrorStatus AES_GroupWriteAndRead_128BIT(uint8_t *dataIn, uint8_t *dataOut);
FL_ErrorStatus AES_GroupWriteAndRead_128BIT_IVR(uint8_t *dataIn, uint8_t *dataOut);
FL_ErrorStatus AES_Init(uint32_t KeyLength, uint32_t CipherMode, uint32_t OperationMode, uint32_t DataType);
FL_ErrorStatus AES_EncryptionAndDecryption(uint8_t *keyIn, uint32_t keyLen, uint8_t *ivrIn, uint8_t *dataIn, uint32_t dataInLen, uint8_t *dataOut, uint32_t *dataOutLen);
FL_ErrorStatus AES_ECB_Encrypt(void);
FL_ErrorStatus AES_ECB_Decrypt(void);
FL_ErrorStatus AES_CTR_Encrypt(void);
FL_ErrorStatus AES_CTR_Decrypt(void);
FL_ErrorStatus AES_CBC_Encrypt(void);
FL_ErrorStatus AES_CBC_Decrypt(void);
FL_ErrorStatus AES_MULTH(void);
#ifdef __cplusplus
}
#endif

#endif /* __AES_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
