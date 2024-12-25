#ifndef RCHFTRIM_H
#define RCHFTRIM_H

#include <stdint.h>
#include <stdbool.h>
#include "fm33lg0xx.h"

int32_t RchfTrimInit(void);
int32_t RchfTrimDeInit(void);
int32_t RchfTrimCalculte(uint8_t *trim);

int32_t RchfTrim(uint8_t *trim, uint16_t count);
bool RchfTrimCheck(uint8_t *trim, uint16_t count, uint8_t limit);

void RchfFoutOutput(void);

#endif
