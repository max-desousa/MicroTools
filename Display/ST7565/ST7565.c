#include "ST7565.h"


void ST7565_Init(struct ST7565 *_display){

    __pinAssignments__(_display);

    __ST7565InitializationWithOnBoardPower__(_display);

    ST7565_SetFirstLine(_display, 0);
}

void ST7565_SetColor(struct ST7565 *_display, int _red, int _green, int _blue) {
    pwm_set_chan_level(pwm_gpio_to_slice_num(_display->pinRed), pwm_gpio_to_channel(_display->pinRed), (255 -_red));
    pwm_set_chan_level(pwm_gpio_to_slice_num(_display->pinGreen), pwm_gpio_to_channel(_display->pinGreen), (255 - _green));
    pwm_set_chan_level(pwm_gpio_to_slice_num(_display->pinBlue), pwm_gpio_to_channel(_display->pinBlue), (255 - _blue));
}

void ST7565_SetFirstLine(struct ST7565 *_display, uint8_t _line) {
    gpio_put(_display->pinCS, false);
    uint8_t formattedLine = 0b01000000 | (0b00111111 & (_line + _display->firstLineCorrector));
    //uint8_t formattedLine = 0b01100100;
    spi_write_blocking(_display->spiInstance, &formattedLine, 1);
    gpio_put(_display->pinCS, true);
}

void ST7565_WritePixels(struct ST7565 *_display, uint8_t _page, uint8_t _column, uint8_t *_src, int _len) {
    gpio_put(_display->pinCS, false);

    uint8_t formattedPage = (0b00001111 & _page) | 0b10110000;
    uint8_t formattedColumnMSB = ((0b11110000 & _column)>>4) | 0b00010000;
    uint8_t formattedColumnLSB = 0b00001111 & _column;

    uint8_t displayOn = 0b10101111;

    spi_write_blocking(_display->spiInstance, &displayOn, 1);

    spi_write_blocking(_display->spiInstance, &formattedPage, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);

    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, _src, _len);
    gpio_put(_display->pinA0, false);
    gpio_put(_display->pinCS, true);
}

void __pinAssignments__(struct ST7565 *_display) {
    gpio_init(_display->pinA0);
    gpio_set_dir(_display->pinA0, GPIO_OUT);
    gpio_put(_display->pinA0, false);

    gpio_init(_display->pinRst);
    gpio_set_dir(_display->pinRst, GPIO_OUT);
    gpio_put(_display->pinRst, true);

    gpio_set_function(_display->pinRed, GPIO_FUNC_PWM);
    gpio_set_function(_display->pinGreen, GPIO_FUNC_PWM);
    gpio_set_function(_display->pinBlue, GPIO_FUNC_PWM);

    pwm_set_wrap(pwm_gpio_to_slice_num(_display->pinRed), 254);
    pwm_set_wrap(pwm_gpio_to_slice_num(_display->pinGreen), 254);
    pwm_set_wrap(pwm_gpio_to_slice_num(_display->pinBlue), 254);

    pwm_set_enabled(pwm_gpio_to_slice_num(_display->pinRed), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(_display->pinGreen), true);
    pwm_set_enabled(pwm_gpio_to_slice_num(_display->pinBlue), true);

    gpio_set_function(_display->pinCLK, GPIO_FUNC_SPI);
    gpio_set_function(_display->pinMOSI, GPIO_FUNC_SPI);

    spi_init(_display->spiInstance, 1000000);

    gpio_init(_display->pinCS);
    gpio_set_dir(_display->pinCS, GPIO_OUT);
    gpio_put(_display->pinCS, true);
}

void __ST7565InitializationWithOnBoardPower__(struct ST7565 *_display) {
    uint8_t bias7 = 0b10100011;
    uint8_t adcNormal = 0b10100000;
    uint8_t commonMode = 0b11000000;
    uint8_t powerMode1 = 0b00101100;
    uint8_t powerMode2 = 0b00101110;
    uint8_t powerMode3 = 0b00101111;
    uint8_t resistorRation = 0b00100110;

    gpio_put(_display->pinCS, false);
    gpio_put(_display->pinRst, false);
    sleep_ms(50);
    gpio_put(_display->pinRst, true);
    sleep_ms(50);
    spi_write_blocking(_display->spiInstance, &bias7, 1);
    //sleep_ms(1000);
    spi_write_blocking(_display->spiInstance, &adcNormal, 1);
    //sleep_ms(1000);
    spi_write_blocking(_display->spiInstance, &commonMode, 1);
    //sleep_ms(1000);
    spi_write_blocking(_display->spiInstance, &powerMode1, 1);
    sleep_ms(50);
    spi_write_blocking(_display->spiInstance, &powerMode2, 1);
    sleep_ms(50);
    spi_write_blocking(_display->spiInstance, &powerMode3, 1);
    sleep_ms(50);
    spi_write_blocking(_display->spiInstance, &resistorRation, 1);
    gpio_put(_display->pinCS, true);
}

void __writeAllToZero__(struct ST7565 *_display) {
    gpio_put(_display->pinCS, false);
    gpio_put(_display->pinA0, false);

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

    spi_write_blocking(_display->spiInstance, &pageOne, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    
    spi_write_blocking(_display->spiInstance, &pageTwo, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    
    spi_write_blocking(_display->spiInstance, &pageThree, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    
    spi_write_blocking(_display->spiInstance, &pageFour, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    
    spi_write_blocking(_display->spiInstance, &pageFive, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    
    spi_write_blocking(_display->spiInstance, &pageSix, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    
    spi_write_blocking(_display->spiInstance, &pageSeven, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);
    
    spi_write_blocking(_display->spiInstance, &pageEight, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);

    spi_write_blocking(_display->spiInstance, &pageNine, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnMSB, 1);
    spi_write_blocking(_display->spiInstance, &formattedColumnLSB, 1);
    gpio_put(_display->pinA0, true);
    spi_write_blocking(_display->spiInstance, zerosArray, 132);
    gpio_put(_display->pinA0, false);
    
    spi_write_blocking(_display->spiInstance, &displayOn, 1);

    gpio_put(_display->pinCS, true);
    gpio_put(25, true);

}