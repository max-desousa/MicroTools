#ifndef MAX_DESOUSA_SIMPLE_PICO_I2C
#define MAX_DESOUSA_SIMPLE_PICO_I2C

#include "stdint.h"
#include "stdio.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

//bool I2c0BusInUse = false;
//bool I2c1BusInUse = false;

uint8_t SetupI2cBus(i2c_inst_t *i2c, uint8_t _sdaPin, uint8_t _sclPin, uint32_t _baudRate);

#endif
