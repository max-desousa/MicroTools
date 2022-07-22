#ifndef MICRO_TOOLS_MICROLESS_I2C
#define MICRO_TOOLS_MICROLESS_I2C

#include "stdlib.h"
#include "stdint.h"

#include "simplePico/i2c.h"

void SendI2cMessage(void *_microSetup, uint8_t *_payload, uint32_t _length);

#endif
