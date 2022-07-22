#include "simplePico/i2c.h"

uint32_t SetupI2cBus(uint8_t _sdaPin, uint8_t _sclPin, uint32_t _baudRate)
  {
  /* Local Variables */
  uint8_t i2cBus;
  i2c_inst_t *i2c;

  /* verify the data and clock pins match - bail out w/ 0xFF if they don't */
  i2cBus = GetPicoI2cBusFromPins(_sdaPin, _sclPin);
  if (i2cBus > 1) return 0xFF;

  /* Set up the GPIO as I2C */
  gpio_set_function(_sdaPin, GPIO_FUNC_I2C);
  gpio_set_function(_sclPin, GPIO_FUNC_I2C);
  gpio_pull_up(_sdaPin);
  gpio_pull_up(_sclPin);
  
  /* Init the I2C bus that we preciously verified */
  i2c = (i2cBus == 0) ? i2c0 : i2c1;
  return i2c_init(i2c, _baudRate);
  }

uint8_t GetPicoI2cBusFromPins(uint8_t _sdaPin, uint8_t _sclPin)
  {
  uint8_t busForDataPin = 0xFF;
  uint8_t busForClockPin = 0xFF;
  switch(_sdaPin)
    {
    case 1:
    case 6:
    case 11:
    case 16:
    case 21:
    case 26:
      busForDataPin = 0x00;
      break;
    case 4:
    case 9:
    case 14:
    case 19:
    case 24:
    case 31:
      busForDataPin = 0x01;
      break;
    default:
      break;
    }
  switch(_sclPin)
    {
    case 2:
    case 7:
    case 12:
    case 17:
    case 22:
    case 27:
      busForClockPin = 0x00;
      break;
    case 5:
    case 10:
    case 15:
    case 20:
    case 25:
    case 32:
      busForClockPin = 0x01;
      break;
    default:
      break;
    }
  if (busForDataPin == busForClockPin)
    {
    return busForDataPin;
    }
  else
    {
    return 0xFF;
    }
  }
