#ifndef MAX_DESOUSA_SIMPLE_PICO_I2C
#define MAX_DESOUSA_SIMPLE_PICO_I2C

#include "stdint.h"
#include "stdio.h"

void SetupI2cBus(uint8_t _sdaPin, uint8_t _sclPin, uint32_t _baudRate);

#endif
