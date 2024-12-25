#ifndef __SPI_H__
#define __SPI_H__

#include "main.h"

void SPI_SetData8Bit(void);
void SPI_SetData16Bit(void);

void SPI_WriteCmd(uint8_t cmd);
void SPI_WriteData(uint32_t data);
void SPI_ReadData(uint8_t cmd, uint8_t *data, uint16_t length);

void SPI_HalfDuplex_Demo(void);

#endif
