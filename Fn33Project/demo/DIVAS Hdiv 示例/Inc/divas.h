
#ifndef __DIVAS_H
#define __DIVAS_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

FL_ErrorStatus DIVAS_Init(void);
FL_ErrorStatus DIVAS_Hdiv(void);
FL_ErrorStatus DIVAS_Root(void);

#ifdef __cplusplus
}
#endif

#endif /* __DIVAS_H */

/************************ (C) COPYRIGHT FMSH *****END OF FILE****/
