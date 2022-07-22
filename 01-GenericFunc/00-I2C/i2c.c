#include "microless/i2c.h"

void SendI2cMessage(T_MCLS_s_I2cModule *_microSetup, uint8_t *_payload, uint32_t _length)
  {
  /* We'll compile with raspberry pi pico code if the project has been
   * configured to use this micro controller */
  #ifdef MICRO_TOOLS_MICRO_PICO
  i2c_write_blocking(_microSetup->i2cBus, _microSetup->address, _payload, _length, false);
  #endif
  }
