#ifndef __RNG_H
#define __RNG_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

FL_ErrorStatus RNG_Function(void);
FL_ErrorStatus RNG_Init(void);
FL_ErrorStatus CRC32_MPEG2_Function(void);

#ifdef __cplusplus
}
#endif

#endif /* __RNG_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
