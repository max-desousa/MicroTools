#ifndef PROJECT_TEMP_ST7565_H
#define PROJECT_TEMP_ST7565_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/spi.h"

struct ST7565 {
    int pinRed;
    int pinGreen;
    int pinBlue;
    int pinCLK;
    int pinMOSI;
    int pinCS;
    spi_inst_t *spiInstance;
    int pinA0;
    int pinRst;
    int firstLineCorrector;
};

void __pinAssignments__(struct ST7565 *_display);
void __ST7565InitializationWithOnBoardPower__(struct ST7565 *_display);

void ST7565_Init(struct ST7565 *_display);
void ST7565_SetColor(struct ST7565 *_display, int _red, int _green, int _blue);
void ST7565_SetFirstLine(struct ST7565 *_display, uint8_t _line);
void ST7565_WritePixels(struct ST7565 *_display, uint8_t _page, uint8_t _column, uint8_t *_src, int _len);

void __writeAllToZero__(struct ST7565 *_display);

#endif //PROJECT_TEMP_ST7565_H
