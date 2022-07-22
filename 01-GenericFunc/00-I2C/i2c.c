#include "microless/i2c.h"

void SendI2cMessage(void *_microSetup, uint8_t *_payload, uint32_t)
  {
  /* We'll compile with raspberry pi pico code if the project has been
   * configured to use this micro controller */
  #ifdef MICRO_TOOLS_MICRO_PICO
  
  #endif
  }
