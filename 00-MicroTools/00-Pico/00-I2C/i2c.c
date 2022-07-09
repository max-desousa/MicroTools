#include "simplePico/i2c.h"

uint8_t SetupI2cBus(i2c_inst_t *i2c, uint8_t _sdaPin, uint8_t _sclPin, uint32_t _baudRate)
  {
  gpio_set_function(_sdaPin, GPIO_FUNC_I2C);
  gpio_set_function(_sclPin, GPIO_FUNC_I2C);
  gpio_pull_up(_sdaPin);
  gpio_pull_up(_sclPin);
  i2c_init(i2c, _baudRate);
  }
