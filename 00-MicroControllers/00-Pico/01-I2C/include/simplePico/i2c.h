#ifndef MAX_DESOUSA_SIMPLE_PICO_I2C
#define MAX_DESOUSA_SIMPLE_PICO_I2C

#include "stdint.h"
#include "stdio.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

typedef struct i2c_struct
  {
  uint8_t dataPin;
  uint8_t clockPin;
  uint32_t baudRate;
  } i2c_struct;

typedef struct spi_struct
  {
  uint8_t misoPin;
  uint8_t mosiPin;
  uint8_t chipSelectPin;
  uint32_t baudRate;
  } spi_struct;


//bool I2c0BusInUse = false;
//bool I2c1BusInUse = false;

uint32_t SetupI2cBus(uint8_t _sdaPin, uint8_t _sclPin, uint32_t _baudRate);
uint8_t GetPicoI2cBusFromPins(uint8_t _sdaPin, uint8_t _sclPin);

#endif
