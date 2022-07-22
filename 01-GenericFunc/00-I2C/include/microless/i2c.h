#ifndef MICRO_TOOLS_MICROLESS_I2C
#define MICRO_TOOLS_MICROLESS_I2C

#include "stdlib.h"
#include "stdint.h"

/* Raspberry Pi Pico i2c header file */
#include "hardware/i2c.h"

#include "simplePico/i2c.h"

typedef struct T_MCLS_s_I2cModule
  {
  uint8_t sdaPin;
  uint8_t sclPin;
  uint32_t baudRate;
  uint8_t address;
  uint8_t i2cBus;
  } T_MCLS_s_I2cModule;

void SendI2cMessage(T_MCLS_s_I2cModule *_microSetup, uint8_t *_payload, uint32_t _length);

#endif
