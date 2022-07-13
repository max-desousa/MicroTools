#ifndef MICRO_TOOLS_GPS_ZEDF9P_H
#define MICRO_TOOLS_GPS_ZEDF9P_H

#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "simplePico/i2c.h"

typedef enum
  {
  i2c,
  spi
  } commsMethod;

bool SimpleSetupZedf9p(commsMethod _method, void *_commsSetup);

#endif
