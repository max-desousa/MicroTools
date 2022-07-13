#include "gps/zedf9p.h"

bool SimpleSetupZedf9p(commsMethod _method, void *_commsSetup)
  {
  bool retVal;
  uint32_t actualBaudRate = 0;
  uint32_t desiredBaudRate = 0;

  switch (_method)
    {
    case i2c:
      ;
      i2c_struct* i2c_setup;
      actualBaudRate = SetupI2cBus(i2c_setup->dataPin, i2c_setup->clockPin, i2c_setup->baudRate);
      desiredBaudRate = i2c_setup->baudRate;
      break;
    case spi:
      retVal = false;
      break;
    default:
      return false;
    }
  if (abs(actualBaudRate - desiredBaudRate) > (desiredBaudRate / 10))
    {
    retVal = false;
    }
  else
    {
    retVal = true;
    }
  return retVal;
  }
