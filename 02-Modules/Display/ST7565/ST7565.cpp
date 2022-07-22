//
// Created by max on 11/22/21.
//

#include <Display/ST7565.hpp>

/*
void ST7565::__pinAssignments__(ST7565 *_display);

void ST7565::__ST7565InitializationWithOnBoardPower__(ST7565 *_display);

void ST7565::ST7565_Init(ST7565 *_display);

void ST7565::ST7565_SetColor(ST7565 *_display, int _red, int _green, int _blue);

void ST7565::ST7565_SetFirstLine(ST7565 *_display, uint8_t _line);

void ST7565::ST7565_WritePixels(ST7565 *_display, uint8_t _page, uint8_t _column, uint8_t *_src, int _len);

void ST7565::__writeAllToZero__(ST7565 *_display);
*/

Display::ST7565::ST7565(int _redPin, int _greenPin, int _bluePin, int _clockPin, int _mosiPin, int _csPin, int _a0Pin,
                        int _rstPin, spi_inst *_spiInstance, int _firstLineCorrection) {
    pinA0 = _a0Pin;
    gpio_init(pinA0);
    gpio_set_dir(pinA0, GPIO_OUT);
    gpio_put(pinA0, false);

    pinRst = _rstPin;
    gpio_init(pinRst);
    gpio_set_dir(pinRst, GPIO_OUT);
    gpio_put(pinRst, true);

    pinRed = _redPin;
    pinGreen = _greenPin;
    pinBlue = _bluePin;
    gpio_set_function(pinRed, GPIO_FUNC_PWM);
    gpio_set_function(pinGreen, GPIO_FUNC_PWM);
    gpio_set_function(pinBlue, GPIO_FUNC_PWM);

    pwm_set_wrap(pwm_gpio_to_slice_num(pinRed), 254);
    pwm_set_wrap(pwm_gpio_to_slice_num(pinGreen), 254);
    pwm_set_wrap(pwm_gpio_to_slice_num(pinBlue), 254);

    pwm_set_enabled(pwm_gpio_to_slice_num(pinRed), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(pinGreen), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(pinBlue), true);

    pinCLK = _clockPin;
    pinMOSI = _mosiPin;
    gpio_set_function(pinCLK, GPIO_FUNC_SPI);
    gpio_set_function(pinMOSI, GPIO_FUNC_SPI);

    spiInstance = _spiInstance;
    spi_init(spiInstance, 1000000);

    pinCS = _csPin;
    gpio_init(pinCS);
    gpio_set_dir(pinCS, GPIO_OUT);
    gpio_put(pinCS, true);

    firstLineCorrector = _firstLineCorrection;

    __ST7565InitializationWithOnBoardPower__();

    SetFirstLine(0);
}

void Display::ST7565::__ST7565InitializationWithOnBoardPower__() const {
    uint8_t bias7 = 0b10100011;
    uint8_t adcNormal = 0b10100000;
    uint8_t commonMode = 0b11000000;
    uint8_t powerMode1 = 0b00101100;
    uint8_t powerMode2 = 0b00101110;
    uint8_t powerMode3 = 0b00101111;
    uint8_t resistorRation = 0b00100110;

    gpio_put(pinCS, false);
    gpio_put(pinRst, false);
    sleep_ms(50);
    gpio_put(pinRst, true);
    sleep_ms(50);
    spi_write_blocking(spiInstance, &bias7, 1);
    spi_write_blocking(spiInstance, &adcNormal, 1);
    spi_write_blocking(spiInstance, &commonMode, 1);
    spi_write_blocking(spiInstance, &powerMode1, 1);
    spi_write_blocking(spiInstance, &powerMode2, 1);
    sleep_ms(50);
    spi_write_blocking(spiInstance, &powerMode3, 1);
    sleep_ms(50);
    spi_write_blocking(spiInstance, &resistorRation, 1);
    gpio_put(pinCS, true);
}

void Display::ST7565::SetFirstLine(uint8_t _line) {
    gpio_put(pinCS, false);
    uint8_t formattedLine = 0b01000000 | (0b00111111 & (_line + firstLineCorrector));
    spi_write_blocking(spiInstance, &formattedLine, 1);
    gpio_put(pinCS, true);
}

void Display::ST7565::SetColor(int _red, int _green, int _blue) {
    pwm_set_chan_level(pwm_gpio_to_slice_num(pinRed), pwm_gpio_to_channel(pinRed), (255 -_red));
    pwm_set_chan_level(pwm_gpio_to_slice_num(pinGreen), pwm_gpio_to_channel(pinGreen), (255 - _green));
    pwm_set_chan_level(pwm_gpio_to_slice_num(pinBlue), pwm_gpio_to_channel(pinBlue), (255 - _blue));
}



void Display::ST7565::WritePixels(uint8_t _page, uint8_t _column, uint8_t *_src, int _len) {
    gpio_put(pinCS, false);

    uint8_t formattedPage = (0b00001111 & _page) | 0b10110000;
    uint8_t formattedColumnMSB = ((0b11110000 & _column)>>4) | 0b00010000;
    uint8_t formattedColumnLSB = 0b00001111 & _column;

    uint8_t displayOn = 0b10101111;

    spi_write_blocking(spiInstance, &displayOn, 1);

    spi_write_blocking(spiInstance, &formattedPage, 1);
    spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(spiInstance, &formattedColumnLSB, 1);

    gpio_put(pinA0, true);
    spi_write_blocking(spiInstance, _src, _len);
    gpio_put(pinA0, false);
    gpio_put(pinCS, true);
}


void Display::ST7565::__writeAllToZero__() {
   gpio_put(pinCS, false);
   gpio_put(pinA0, false);

   uint8_t pageOne = 0b10110000;
   uint8_t pageTwo = 0b10110001;
   uint8_t pageThree = 0b10110010;
   uint8_t pageFour = 0b10110011;
   uint8_t pageFive = 0b10110100;
   uint8_t pageSix = 0b10110101;
   uint8_t pageSeven = 0b10110110;
   uint8_t pageEight = 0b10110111;
   uint8_t pageNine = 0b10111000;
   uint8_t formattedColumnMSB = 0b00010000;
   uint8_t formattedColumnLSB = 0b00000000;
   uint8_t displayOn = 0b10101111;

   uint8_t zerosArray[132] = {
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   };

   spi_write_blocking(spiInstance, &pageOne, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);


   spi_write_blocking(spiInstance, &pageTwo, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);


   spi_write_blocking(spiInstance, &pageThree, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);


   spi_write_blocking(spiInstance, &pageFour, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);


   spi_write_blocking(spiInstance, &pageFive, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);


   spi_write_blocking(spiInstance, &pageSix, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);


   spi_write_blocking(spiInstance, &pageSeven, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);

   spi_write_blocking(spiInstance, &pageEight, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);

   spi_write_blocking(spiInstance, &pageNine, 1);
   spi_write_blocking(spiInstance, &formattedColumnMSB, 1);
   spi_write_blocking(spiInstance, &formattedColumnLSB, 1);
   gpio_put(pinA0, true);
   spi_write_blocking(spiInstance, zerosArray, 132);
   gpio_put(pinA0, false);

   spi_write_blocking(spiInstance, &displayOn, 1);

   gpio_put(pinCS, true);
   gpio_put(25, true);

}
